#ifndef sound_h
#define sound_h

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "video.h"

class Sound{
    public:
    //constructor
    Sound() : plays(0), count(0){}

    //modifiers
    void add_count(){count += 1;}
    void add_plays(const long unsigned int aPlays){plays += aPlays;}
    void set_music_name(const std::string& aMusic_name){music_name = aMusic_name;}
    void set_music_author(const std::string& aMusic_author){music_author = aMusic_author;}
    void set_music_id(const std::string& aMusic_id){music_id = aMusic_id;}

    //accessors
    std::string get_music_name() const {return music_name;}
    long unsigned int get_plays() const {return plays;}
    std::string get_music_author() const {return music_author;}
    std::string get_music_id() const {return music_id;}
    long unsigned int get_count() const {return count;}
    const std::vector<Video>& get_vids() const {return vids;}
    std::vector<Video>& get_vids(){return vids;}

    //member functions
    bool operator<(const Sound& other) const;

    private:
    std::string music_name;
    long unsigned int plays;
    std::string music_author;
    std::string music_id;
    long unsigned int count;
    std::vector<Video> vids;
};
//non-member functions
void create_sounds(std::unordered_map<std::string, Sound>& map, Video& vid);
void create_sound_map(std::unordered_map<std::string, Sound>& map, std::string& inputFile);
std::ostream& operator<< (std::ostream& os, const Sound& sound);
#endif