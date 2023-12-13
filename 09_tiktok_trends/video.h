#ifndef video_h
#define video_h

#include <string>
#include <vector>
#include <regex>
#include <iostream>

class Video{
    public:
    //modifiers
    void set_cover_url(const std::string& url){cover_url = url;}
    void set_web_video_url(const std::string& web_url){web_video_url = web_url;}
    void set_plays(const unsigned long aPlays){plays = aPlays;}
    void set_music_name(const std::string& aMusic_name){music_name = aMusic_name;}
    void set_music_author(const std::string& aMusic_author){music_author = aMusic_author;}
    void set_music_id(const std::string& aMusic_id){music_id = aMusic_id;}
    void set_likes(const unsigned long aLikes){likes = aLikes;}
    void set_tags(const std::vector<std::string>& aTags){tags = aTags;}

    //accessors
    std::string get_cover_url() const {return cover_url;}
    std::string get_web_video_url() const {return web_video_url;}
    unsigned long get_plays() const {return plays;}
    std::string get_music_name() const {return music_name;}
    std::string get_music_author() const {return music_author;}
    std::string get_music_id() const {return music_id;}
    unsigned long get_likes() const {return likes;}   
    std::vector<std::string> get_tags() const {return tags;}

    //member functions
    bool operator>(const Video& other);
    bool operator<(const Video& other);

    private:
    std::string cover_url;
    std::string web_video_url;
    unsigned long plays;
    std::string music_name;
    std::string music_author;
    std::string music_id;
    unsigned long likes;
    std::vector<std::string> tags;
};
//non-member functions
void create_video(std::string& line, Video& vid);
std::ostream& operator<< (std::ostream& os, const Video& vid);
void add_vid(std::vector<Video>& vids, Video vid);
bool video_sort(const Video& a, const Video& b);
#endif