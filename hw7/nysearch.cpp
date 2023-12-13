#include <regex>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include <algorithm>


//prototypes
std::list<std::string> extractLinksFromHTML(const std::string& fileContent);
void web_crawler(std::string seedFile, std::set <std::string>& files);
void create_inverted_index(std::map <std::string, std::set<std::string> >& inverse_index, const std::vector<std::string>& search, const std::set<std::string>& files);
std::string file_body(const std::string& file);
std::set<std::string> querey_searching(std::map <std::string, std::set<std::string> >& inverted_index, 
bool phrase_search, std::vector<std::string>& search);
void page_ranking(const std::set<std::pair<std::string, double> >& back_links_set, const std::set<std::pair<std::string, double> >& keyword_set,
 std::set<std::pair<double, std::string> >& sorted_files);
void keyword_density(std::set<std::pair<std::string, double> >& keyword_set, const std::vector<std::string>& search,
 const std::set<std::string>& valid_files, const std::set<std::string>& files);
void back_links(const std::set<std::string>& files, std::set<std::pair<std::string, double> >& back_link_set,
 const std::set<std::string>& valid_files);
void print_files(std::set<std::pair<double,std::string> >& sorted_files, const std::vector<std::string>& search, const bool phrase_search,std::ofstream& outFile);
std::string get_title(const std::string& file);
std::string get_description(const std::string& file);
std::string get_snippet(const std::string& file, const std::vector<std::string>& search, const bool phrase_search);



int main(int argc, char* argv[]){
    //file error checking 
    std::ofstream outFile(argv[2]);
    if(!outFile.good()){
        std::cerr << "Can not open " << std::string(argv[2]) << " to write!" << std::endl;
        exit(1);
    }

    //getting the search query
    bool phrase_search = false;
    std::vector<std::string> search;
    for(unsigned int i = 3; i < argc; i++){
        size_t quotePos;
        std::string temp;
        temp = (argv[i]);
        if((quotePos = temp.find('"')) != std::string::npos){
            temp.erase(quotePos, 1);
            phrase_search = true;
        }
        search.push_back(temp);
    }
    //set of all html files start empty
    std::set <std::string> files;
    //get a set of the path to every file
    //allows easy access
    web_crawler((std::string(argv[1])), files);

    //inverted index
    std::map <std::string, std::set<std::string> > inverted_index;
    create_inverted_index(inverted_index, search, files);

    //finding valid files
    std::set <std::string> valid_files;
    valid_files = querey_searching(inverted_index, phrase_search, search);

    //error checking to check if there are any matches
    if(valid_files.size() == 0){
        outFile << "Your search - ";
        if(phrase_search == true){
            outFile << '"';
            for(unsigned int i = 0; i < search.size(); i++){
                if(i == search.size() - 1){
                    outFile << search[i];
                }else{
                    outFile << search[i] << " ";
                }
            }
            outFile << '"';
        }else{
            for(unsigned int i = 0; i < search.size(); i++){
                if(i == search.size() - 1){
                    outFile << search[i];
                }else{
                    outFile << search[i] << " ";
                }
            }
        }
        outFile << " - did not match any documents.";
    }
    
    //calculating keyword density scores
    std::set<std::pair<std::string, double> > keyword_set;
    keyword_density(keyword_set, search, valid_files, files);

    //calculating back link scores
    std::set<std::pair<std::string, double> > back_links_set;
    back_links(files, back_links_set, valid_files);

    //calculating overall page scores
    std::set<std::pair<double, std::string> > sorted_files;
    page_ranking(back_links_set, keyword_set, sorted_files);

    //printing the files
    print_files(sorted_files, search, phrase_search, outFile);

    return 0;
}

void web_crawler(std::string seedFile, std::set <std::string>& files){
    //function that goes through all of the files
    //via the urls in those files starting at seed file
    //add each file path to a set if a file path
    //cannot be added to the set it has already been
    //visited so the function call ends
    //at the end of recursion a set of all file paths is created
    bool added;
    added = files.insert(seedFile).second;
    if(added == false){
        return;
    }
    std::ifstream fileStream(seedFile);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        std::list<std::string> links_list = extractLinksFromHTML(fileContent);
        for(std::list<std::string>::iterator it = links_list.begin(); it != links_list.end(); it++){
            std::string directory;
            // suppose URL is "html_files/subdir1/subdir2/file7.html"
            size_t lastSlashPos = seedFile.find_last_of('/');
            if (lastSlashPos != std::string::npos) {
                // directory will now be "html_files/subdir1/subdir2/"
                directory = seedFile.substr(0, lastSlashPos + 1);
            }
            if((*it)[0] != '.'){
                directory += (*it);
                web_crawler((directory), files);
            }
        }
    }
}

std::list<std::string> extractLinksFromHTML(const std::string& fileContent) {
    std::list<std::string> links;
    // regular expression to match href attributes in anchor tags
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    std::smatch match;

    // search for links in the HTML content
    std::string::const_iterator start = fileContent.cbegin();
    while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }
    return links;
}

void create_inverted_index(std::map <std::string, std::set<std::string> >& inverted_index, const std::vector<std::string>& search, 
const std::set<std::string>& files)
{
    //loop through all the search words
    //add every file that the words appear in to a set
    //at the end make a pair of the search word and the set
    //add that pair to the map
    //at end of fucntion should have complete inverted index
    for(unsigned int i = 0; i < search.size(); i++){
        std::set<std::string> appears;
        for(std::set<std::string>::iterator it = files.begin(); it != files.end(); it++){
            std::string body = file_body((*it));
            if(body.find(search[i]) != std::string::npos){
                appears.insert((*it));
            }
        }
        inverted_index[search[i]] = appears;
    }
}

std::string file_body(const std::string& file){
    //function to isolate the body of the html file
    //looks for the two occurences of <body>
    //returns everything in bewteen 
    std::string body;
    std::ifstream fileStream(file);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        size_t found1 = fileContent.find("<body>");
        size_t found2 = fileContent.find("<body>", found1+1);
        body = fileContent.substr(found1 + 6 , (found2 - found1 - 6));
    }
    return body;
}

std::set<std::string> querey_searching(std::map <std::string, std::set<std::string> >& inverted_index, 
bool phrase_search, std::vector<std::string>& search)
{
    //if there is only one word phrase or regular search don't matter
    //return the set from the inverted index
    if(inverted_index.size() == 1){
        return (inverted_index.begin()->second);
    }

    //if it is a regular search
    //comapare the sets in the inverted index for each 
    //key, then return the intersection of the sets
    if(phrase_search == false){
        std::set<std::string> valid_files;
        valid_files = inverted_index[search[0]];
        for(unsigned int i = 1; i < search.size(); i++){
            std::set<std::string> temp;
            std::set_intersection(valid_files.begin(), valid_files.end(),
            inverted_index[search[i]].begin(), inverted_index[search[i]].end(),
            std::inserter(temp, temp.begin()));
            valid_files = temp;
        }
        return valid_files;
    }else{
        //if it is a phrase search
        //create a string containing the whole phrase
        //then look at the body of every file in 
        //the set of the first key in the inverted index
        //create a set that contains all the files
        //where the phrase was found
        std::string whole_phrase;
        for(unsigned int i = 0; i < search.size(); i++){
            whole_phrase += (' ' + search[i]);
        }
        std::set<std::string> valid_files;
        std::set<std::string> temp;
        temp = inverted_index[search[0]];
        for(std::set<std::string>::iterator it = temp.begin(); it != temp.end(); it++){
            std::string body = file_body((*it));
            size_t found = body.find(whole_phrase);
            if(found != std::string::npos){
                valid_files.insert((*it));
            }
        }
        return valid_files;
    }
    
}

void keyword_density(std::set<std::pair<std::string, double> >& keyword_set, const std::vector<std::string>& search,
 const std::set<std::string>& valid_files, const std::set<std::string>& files)
{
    //loop through each word
    //for each word loop through all files
    //count the number of times the word appears accros all files
    //divide that count by total count of file sizes
    //to het overall keyword density for each word
    
    std::vector<double> all_word_densities;
    for(unsigned int i = 0; i < search.size(); i++){
        double word_density = 0;
        double count = 0;
        long unsigned int files_size = 0;
        for(std::set<std::string>::iterator it = files.begin(); it != files.end(); it++){
            std::ifstream fileStream((*it));
            if (fileStream.is_open()) {
                std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
                size_t pos = 0;
                while((pos = fileContent.find((search[i]), pos)) != std::string::npos){
                    count++;
                    pos += search[i].size() + 1;
                }
                files_size += fileContent.size();
            }
        }
        word_density = (count / files_size);
        all_word_densities.push_back(word_density);
    }

    //loop through all valid_files
    //for each file loop through all keywords
    //calculate each keyword density score and add them
    //add each file and score to a set
    for(std::set<std::string>::iterator it = valid_files.begin(); it != valid_files.end(); it++){
        double file_score = 0;
        std::ifstream fileStream((*it));
        if (fileStream.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            long unsigned int file_size = fileContent.size();
            for(unsigned int i = 0; i < search.size(); i++){
                double count = 0;
                size_t pos = 0;
                while((pos = fileContent.find((search[i]), pos)) != std::string::npos){
                    count++;
                    pos += search[i].size() + 1;
                }
                file_score += (count / (file_size * all_word_densities[i]));
            }
                keyword_set.insert(std::make_pair((*it), file_score));
            }
        }
}


void back_links(const std::set<std::string>& files, std::set<std::pair<std::string, double> >& back_link_set,
 const std::set<std::string>& valid_files)
{
    //loop through each valid file and get its name/directory
    //go through every file and get its outgoing links
    //get each of those linkes names/directories
    //if the valid files name is in it 
    //use formula and add it to score
    //add score and file name to set
    for(std::set<std::string>::iterator it = valid_files.begin(); it != valid_files.end(); it++){
        double score = 0;
        std::string directory;
        // suppose URL is "html_files/subdir1/subdir2/file7.html"
        size_t lastSlashPos = (*it).find_last_of('/');
        if (lastSlashPos != std::string::npos) {
            // directory will now be "file7.html"
            directory = (*it).substr(lastSlashPos + 1, (*it).size());
        }else{
            directory = (*it);
        }


        for(std::set<std::string>::iterator it_2 = files.begin(); it_2 != files.end(); it_2++){
            std::ifstream fileStream((*it_2));
            if (fileStream.is_open()) {
                std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
                std::list<std::string> file_links = extractLinksFromHTML(fileContent);
                for(std::list<std::string>::iterator it_3 = file_links.begin(); it_3 != file_links.end(); it_3++){
                    std::string link;
                    // suppose URL is "html_files/subdir1/subdir2/file7.html"
                    size_t lastSlashPos = (*it_3).find_last_of('/');
                    if (lastSlashPos != std::string::npos && lastSlashPos != 0) {
                        // directory will now be "file7.html"
                        link = (*it_3).substr(lastSlashPos + 1, (*it).size());
                    }else{
                        link = (*it_3);
                    }
                    if(link == directory){
                        score += ((1.0 / (1 + (file_links.size())))); 
                    }
                }
            }
        }
        back_link_set.insert(std::make_pair((*it), score));
    }
}


void page_ranking(const std::set<std::pair<std::string, double> >& back_links_set, const std::set<std::pair<std::string, double> >& keyword_set,
 std::set<std::pair<double, std::string> >& sorted_files)
{
    //loop through keyword density set and back link set
    //use formula 1 to calculate over all score for each file
    //add the score and the file to a set so they're sorted
    std::set<std::pair<std::string, double> >::iterator it_2 = keyword_set.begin();
    for(std::set<std::pair<std::string, double> >::iterator it = back_links_set.begin(); it != back_links_set.end(); it++, it_2++){
        double page_score = 0;
        double score1 = (*it).second;
        double score2 = (*it_2).second;
        page_score = (0.5 * score2 + 0.5 * score1);
        sorted_files.insert(std::make_pair(page_score, (*it).first));
    }
}


void print_files(std::set<std::pair<double,std::string> >& sorted_files, const std::vector<std::string>& search, const bool phrase_search, std::ofstream& outFile){
    //print out all the sorted files by looping
    //through the list of files in reverse
    //since higher score == better page ranking
    if(sorted_files.size() == 0){
        return;
    }
    outFile << "Matching documents: " << std::endl;
    for(std::set<std::pair<double , std::string> >::reverse_iterator rit = sorted_files.rbegin(); rit != sorted_files.rend(); ++rit){
        outFile << std::endl << "Title: " << get_title((*rit).second) << std::endl
        <<"URL: " << (*rit).second << std::endl
        <<"Description: " << get_description((*rit).second) << std::endl
        <<"Snippet: " << get_snippet(((*rit).second), search, phrase_search) << std::endl;
    }
}

std::string get_title(const std::string& file){
    //get the title from the html file by looking for
    //the words/sybmbols that enclose it and taking a subtr
    //of the words between them
    std::string title;
    std::ifstream fileStream(file);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        int found1 = fileContent.find("<title>");
        int found2 = fileContent.find("</title>", found1+1);
        title = fileContent.substr(found1 + 7, found2-found1 - 7);
        return title;
    }
    return title;
}

std::string get_description(const std::string& file){
    //get the description from the html file by looking for
    //the words/sybmbols that enclose it and taking a subtr
    //of the words between them
    std::string description;
    std::ifstream fileStream(file);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        int found1 = fileContent.find("content=");
        int found2 = fileContent.find(">", found1+1);
        description = fileContent.substr(found1 + 9, found2-found1 - 10);
        return description;
    }
    return description;
}

std::string get_snippet(const std::string& file, const std::vector<std::string>& search, const bool phrase_search){
    std::string snippet;
    std::string body;
    body = file_body(file);
    bool found_phrase =false;
    std::string phrase;
    for(unsigned int i = 0; i < search.size(); i++){
        if(i == search.size()-1){
            phrase += search[i];
        }else{
            phrase += search[i] + ' ';
        }
    }
    //check if the whole phrase is in the body of the file
    //if it is find the period before it
    // start the snippet at the next non whitesapce char
    //create a snippet of 120 chars
    int found = body.find(phrase);
        if(found != std::string::npos){
            found_phrase = true;
            size_t period_pos = body.rfind(".", found);
            if(period_pos != std::string::npos){
                while(std::isspace(body[period_pos + 1])){
                    period_pos += 1;
                }
                snippet = body.substr(period_pos + 1, 120);
            }else{
                snippet = body.substr(found + 1, 121);
            }
        }
    //if the whole phrase is not found
    //repeat all above steps for first occurence
    //of the first key word
    if(found_phrase == false){
        int found = body.find(search[0]);
        if(found != std::string::npos){
            size_t period_pos = body.rfind(".", found);
            if(period_pos != std::string::npos){
                while(std::isspace(body[period_pos + 1])){
                    period_pos += 1;
                }
                snippet = body.substr(period_pos + 1, 120);
            }else{
                snippet = body.substr(found + 1, 120);
            }
        }
    }
    return snippet;
}

