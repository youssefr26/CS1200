#include "video.h"


void create_video(std::string& line, Video& vid){
    std::vector<std::string> tags;
    //get text
    size_t text_found = line.find("\"text\": \"");
    size_t text_end = line.find("\", \"", text_found + 9);
    std::string text = line.substr(text_found + 9, text_end - text_found - 9);
    // the text of the post is given as a std::string, extract hashtags from the text.
    // define a regular expression to match hashtags
    std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");
    // create an iterator for matching
    std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
    std::sregex_iterator endIterator;
    // iterate over the matches and extract the hashtags
    while (hashtagIterator != endIterator) {
        std::smatch match = *hashtagIterator;
        std::string hashtag = match.str(1);  // extract the first capturing group
        tags.push_back(hashtag);
        ++hashtagIterator;
    }
    vid.set_tags(tags);

    //get music name
    size_t music_name_found = line.find("\"musicName\": \"");
    size_t music_name_end = line.find("\", \"", music_name_found + 14);
    std::string music_name = line.substr(music_name_found + 14, music_name_end - music_name_found - 14);
    vid.set_music_name(music_name);

    //get music author
    size_t music_author_found = line.find("\"musicAuthor\": \"");
    size_t music_author_end = line.find("\", \"", music_author_found + 16);
    std::string music_author = line.substr(music_author_found + 16, music_author_end - music_author_found - 16);
    vid.set_music_author(music_author);

    //get music id
    size_t music_id_found = line.find("\"musicId\": \"");
    size_t music_id_end = line.find("\"}", music_id_found + 12);
    std::string music_id = line.substr(music_id_found + 12, music_id_end - music_id_found - 12);
    vid.set_music_id(music_id);

    //get web video url
    size_t web_video_url_found = line.find("\"webVideoUrl\": \"");
    size_t web_video_url_end = line.find("\", \"", web_video_url_found + 16);
    std::string web_video_url = line.substr(web_video_url_found + 16, web_video_url_end - web_video_url_found - 16);
    vid.set_web_video_url(web_video_url);

    //get cover url
    size_t cover_url_found = line.find("\"coverUrl\": \"");
    size_t cover_url_end = line.find("\", \"", cover_url_found + 13);
    std::string cover_url = line.substr(cover_url_found + 13, cover_url_end - cover_url_found - 13);
    vid.set_cover_url(cover_url);

    //get likes
    size_t likes_found = line.find("\"diggCount\": ");
    size_t likes_end = line.find(", \"", likes_found + 13);
    std::string likes = line.substr(likes_found + 13, likes_end - likes_found - 13);
    vid.set_likes(std::stoul(likes));

    //get plays
    size_t plays_found = line.find("\"playCount\": ");
    size_t plays_end = line.find(", \"", plays_found + 13);
    std::string plays = line.substr(plays_found + 13, plays_end - plays_found - 13);
    vid.set_plays(std::stoul(plays));
}

std::ostream& operator<< (std::ostream& os, const Video& vid){
    //prints out the urls for each video object
    os << "cover url: " << vid.get_cover_url() << std::endl
    << "web video url: " << vid.get_web_video_url() << std::endl;
    return os;
}
bool Video::operator>(const Video& other){
    return plays > other.get_plays();
}

bool Video::operator<(const Video& other){
    return plays < other.get_plays();
}

void add_vid(std::vector<Video>& vids, Video vid){
    //function to create and maintain a sorted
    //vector of three videos
    //adds and sorts videos till vector size is three
    //then checks if current object is greater than smallest
    //object in the vector if it is it deletes it and adds
    //the current object then resorts the vector
    if(vids.size() < 3){
        vids.push_back(vid);
        std::sort(vids.begin(), vids.end(), video_sort);
    }else{
        if(vid > vids[2]){
            vids.pop_back();
            vids.push_back(vid);
            std::sort(vids.begin(), vids.end(), video_sort);
        }
        return;
    }
}

bool video_sort(const Video& a, const Video& b){
    return a.get_plays() > b.get_plays();
}
