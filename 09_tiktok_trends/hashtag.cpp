#include "hashtag.h"

void create_hashtags(std::unordered_map<std::string, Hashtag>& map, Video& vid){
    for(unsigned int i = 0; i < (vid.get_tags()).size(); i++){
        //loop through every tag used in the video
        std::unordered_map<std::string, Hashtag>::iterator it;
        it = map.find(((vid.get_tags())[i]));
        if(it == map.end()){
            //if the tag is not already in the map
            //of all the tags, create a new Hashtag
            //populate it and add the video in its 
            //vector of videos
            Hashtag tag;
            tag.set_tag((vid.get_tags())[i]);
            tag.add_plays((vid.get_plays()));
            tag.increase_count();
            add_vid((tag.get_vids()), vid);
            map.insert(std::make_pair(((vid.get_tags())[i]), tag));
        }else{
            //if the tag is already in the map 
            //of all the tags, increase that tag's
            //count and plays and try to add video
            //to the tag's vector of vidoes
            Hashtag& tag = map[((vid.get_tags())[i])];
            tag.increase_count();
            tag.add_plays((vid.get_plays()));
            add_vid((tag.get_vids()), vid);
        }
    }
}

void create_hashtag_map(std::unordered_map<std::string, Hashtag>& map, std::string& json_file){
    // assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream jsonFile(json_file);
    if (!jsonFile.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            exit(1);
    }
    std::string line;
    Video video;
    //loops trhough each line of the json file string
    //creates videos and adds them to Hashtags
    while (std::getline(jsonFile, line)) {
        create_video(line, video);
        create_hashtags(map, video);
    }
}

std::ostream& operator<< (std::ostream& os, const Hashtag& tag){
    //prints out each Hashtag object with the given format
    os << "========================" << std::endl;
    os << "#" << tag.get_tag() << std::endl
    << "used " << tag.get_count() << " times" << std::endl
    << tag.get_plays() << " views" << std::endl << std::endl;
    for(unsigned int i = 0; i < (tag.get_vids()).size(); i++){
        os << ((tag.get_vids())[i]);
    }
    os << "========================" << std::endl;
    return os;
}

bool Hashtag::operator<(const Hashtag& other) const {
    //compares Hashtag objects based on the given perameters
    //given in the read me
    if(count == other.get_count()){
        if(plays == other.get_plays()){
            return other.get_tag() < tag;
        }
        return plays < other.get_plays();
    }
    return count < other.get_count();
}