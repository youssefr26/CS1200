#include "sound.h"

void create_sounds(std::unordered_map<std::string, Sound>& map, Video& vid){
    if(map.find(vid.get_music_id()) == map.end()){
        Sound sound;
        //if the music id is not in the map
        //create a new sound object 
        //fill the object with the info from the video
        //add it to sounds vector of videos
        sound.set_music_author(vid.get_music_author());
        sound.set_music_id(vid.get_music_id());
        sound.set_music_name(vid.get_music_name());
        sound.add_count();
        sound.add_plays(vid.get_plays());
        add_vid((sound.get_vids()), vid);
        map.insert(std::make_pair(vid.get_music_id(), sound));
    }else{
        //if the music id is in the map
        //increase count and views
        //try to add video to vector of videos
        Sound& sound = map[vid.get_music_id()];
        sound.add_count();
        sound.add_plays(vid.get_plays());
        add_vid((sound.get_vids()), vid);
    }
}

void create_sound_map(std::unordered_map<std::string, Sound>& map, std::string& inputFile){
    // assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream jsonFile(inputFile);
    if (!jsonFile.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            exit(1);
    }
    std::string line;
    Video video;
    //loops trhough each line of the json file string
    //creates videos and adds them to a Sound
    while (std::getline(jsonFile, line)) {
        create_video(line, video);
        create_sounds(map, video);
    }
}

std::ostream& operator<< (std::ostream& os, const Sound& sound){
    //prints out sound objects with the given format
    os << "========================" << std::endl;
    os << sound.get_music_name() << std::endl;
    os << sound.get_plays() << " views" << std::endl;
    os << sound.get_music_author() << std::endl;
    os << "music id: " << sound.get_music_id() << std::endl << std::endl;
    for(int i = 0; i < (sound.get_vids()).size(); i++){
        os << (sound.get_vids())[i];
    }
    os << "========================" << std::endl;
    return os;
}

bool Sound::operator<(const Sound& other) const {
    //compares sound objects based on given parameters
    if(plays == other.get_plays()){
        return other.get_music_id() < music_id;
    }
    return plays < other.get_plays();
}