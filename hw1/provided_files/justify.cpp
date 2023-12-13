#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;



//protoypes
void rightJustify(ifstream &inFile, ofstream &outFile, int &width);
void leftJustify(ifstream &inFile, ofstream &outFile, int &width);
void fullJustify(ifstream &inFile, ofstream &outFile, int &width);

int main(int argc, char* argv[]){
    //error checking
    //checking for number of arguements
    if(argc-1 != 4){
    cerr << "Incorrect number of arguements provied: Expected 4 " << "Inputed " << argc << endl;
    exit(1);
    }
    //opening in file to read
    //checking in file
    ifstream inFile(argv[1]);
    if(!inFile.good()){
    cerr << "Can't open " << argv[1] << " to read." << endl;
    exit(1);
    }
    //opening out file to write
    //checking out file
    ofstream outFile(argv[2]);
    if(!outFile.good()){
        cerr << "Can't open " << argv[2] << " to write." << endl;
        exit(1);
    }

    int width = atoi(argv[3]);
    string justy = string(argv[4]);

    if(justy == "flush_left"){
        leftJustify(inFile, outFile, width);
    }else if(justy == "flush_right"){
        rightJustify(inFile, outFile, width);
    }else if(justy == "full_justify"){
        fullJustify(inFile, outFile, width);
    }
    outFile.close();
return 0;
}


void rightJustify(ifstream &inFile, ofstream &outFile, int &width){
    string word;
    vector<string> line;
    int count= 0;
    outFile << string((width + 4), '-') << endl;
    while( inFile >> word){
        //adding words to a vector if they fit on line
        if((count + (word.size()))+1 <= width){
            word = ' ' + word;
            count += ((word.size()));
            line.push_back(word);
        }else{
            //ascii border and spaces for justify
            outFile << "| ";
            int spaces = (width - count);
            outFile << string(spaces,' ');
            //printing each line from the vector
            for(unsigned int i = 0; i < line.size(); i++){
                    outFile << line[i];
            }
            //formatting line
            //clearing vector and setting up new count
            outFile << " |";
            outFile << endl;
            line.clear();
            line.push_back(word);
            count = ((word.size()));
            
        }
    }
    //printing the last line and border
    outFile << "| ";
    int spaces = (width - count);
    outFile << string(spaces, ' ');
    for(unsigned int i = 0; i < line.size(); i++){
        outFile << line[i];
    }
    outFile << " |" << endl;
    outFile << string((width + 4), '-') << endl;

}


void leftJustify(ifstream &inFile, ofstream &outFile, int &width){
 string word;
    vector<string> line;
    int count= 0;
    outFile << string((width + 4), '-') << endl;
    while( inFile >> word){
        //adding words to a vector if they fit on line
        if((count + (word.size())) < width){
            word += ' ';
            count += (word.size());
            line.push_back(word);
        }else if((count + (word.size())) == width){
            count += word.size();
            line.push_back(word);
        }else if(((count + (word.size())) > width) && (word.size() < width)){
            //ascii border and spaces for justify
            outFile << "| ";
            //printing each line from the vector
            for(unsigned int i = 0; i < line.size(); i++){
                outFile << line[i];
            }
            //formatting line
            //clearing vector and setting up new count
            int spaces = (width - count);
            outFile << string(spaces,' ');
            outFile << " |";
            outFile << endl;
            line.clear();
            word += ' ';
            line.push_back(word);
            count = (word.size());
            
        }
        else{
                        //checking for long words
            if(line.size()>0){
                outFile << "| ";
                int lcount = 0;
                //outputting previous line to handle long word
                for(unsigned int i = 0; i < line.size(); i++){
                    outFile << line[i] << ' ';
                    lcount += (line[i].size() + 1);
                }
                line.clear();
                int lspaces = (width - lcount);
                outFile << string(lspaces, ' ');
                outFile << " |" << endl;;
            }
            //splitting up long words to fit line
            while(word.size() > width){
                string newWord;
                for(unsigned int i = 0; i != (width-1); i++){
                    newWord += word[i];
                }
                newWord += '-';
                outFile << "| " << newWord << " |" << endl;
                string temp;
                for(unsigned int i = (width-1); i < word.size(); i++){
                    temp += word[i];
                }
                word = temp;
            }
            word += ' ';
            line.push_back(word);
            count = (word.size());

        }

    }
    //printing the last line and border
    outFile << "| ";
    for(unsigned int i = 0; i < line.size(); i++){
        outFile << line[i];
    }
    int spaces = (width - count);
    outFile << string(spaces, ' ');
    outFile << " |" << endl;
    outFile << string((width + 4), '-') << endl;
}


void fullJustify(ifstream &inFile, ofstream &outFile, int &width){
string word;
vector<string> line;
int count= 0;
outFile << string((width+4), '-') << endl;
int spaces = 0;
while(inFile >> word){
//adding words to a vector if they fit on line
        if((count + (word.size())) < width){
            spaces += 1;
            count += (word.size()+1);
            line.push_back(word);
        }else if((count + (word.size())) == width){
            count += word.size();
            line.push_back(word);
        }else if(((count + (word.size())) > width) && (word.size() < width)){
            outFile << "| ";
            int extra = (width - count);
            spaces += extra;
            //looping through line and adding the spaces 
            //between words in order
            unsigned int i = 0;
            while(spaces != 0){
                if(i == (line.size()-1)){
                    i = 0;
                }else{
                    line[i] += ' ';
                    spaces--;
                    i++;
                }
                
            }
            //printing the vector/line
            for(unsigned int i = 0; i < line.size(); i++){
                outFile << line[i];
            }
            outFile << " |";
            outFile << endl;
            //clearing and starting next line
            line.clear();
            line.push_back(word);
            count = (word.size()+1);
            spaces = 1;
        }else{
            //checking for long words
            if(line.size()>0){
                outFile << "| ";
                int lcount = 0;
                //outputting previous line to handle long word
                for(unsigned int i = 0; i < line.size(); i++){
                    outFile << line[i] << ' ';
                    lcount += (line[i].size() + 1);
                }
                line.clear();
                int lspaces = (width - lcount);
                outFile << string(lspaces, ' ');
                outFile << " |" << endl;;
            }
            //splitting up long words to fit line
            while(word.size() > width){
                string newWord;
                for(unsigned int i = 0; i != (width-1); i++){
                    newWord += word[i];
                }
                newWord += '-';
                outFile << "| " << newWord << " |" << endl;
                string temp;
                for(unsigned int i = (width-1); i < word.size(); i++){
                    temp += word[i];
                }
                word = temp;
            }
            //adding new word that fits to next line
            line.push_back(word);
            count = (word.size()+1);
            spaces += 1;
        }
        
}
    //printing the last line in left justify and border
    outFile << "| ";
    for(unsigned int i = 0; i < line.size(); i++){
        outFile << line[i] << ' ';
    }
    spaces = (width - count);
    outFile << string(spaces, ' ');
    outFile << " |" << endl;
    outFile << string((width + 4), '-') << endl;
}



