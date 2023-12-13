#ifndef hashtag_h
#define hashtag_h

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "video.h"

class Hashtag{
    public:
    //constructor
    Hashtag() : count(0), plays(0) {}

    //modifiers
    void set_tag(const std::string& aTag){tag = aTag;}
    void increase_count(){count += 1;}
    void add_plays(const unsigned long aPlays){plays += aPlays;}

    //accessors
    std::string get_tag() const {return tag;}
    unsigned long get_count() const {return count;}
    unsigned long get_plays() const {return plays;}
    const std::vector<Video>& get_vids() const {return vids;}
    std::vector<Video>& get_vids(){return vids;}

    //member functions
    bool operator<(const Hashtag& other) const;

    private:
    std::string tag;
    unsigned long count;
    unsigned long plays;
    std::vector<Video> vids;
};
//non-member functions
void create_hashtags(std::unordered_map<std::string, Hashtag>& map, Video& vid);
void create_hashtag_map(std::unordered_map<std::string, Hashtag>& map, std::string& json_file);
std::ostream& operator<< (std::ostream& os, const Hashtag& tag);
#endif