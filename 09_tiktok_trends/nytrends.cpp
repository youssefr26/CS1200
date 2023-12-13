#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <queue>

#include "video.h"

#include "hashtag.h"
#include "sound.h"

int main(int argc, char* argv[]){
    //file error checking
    std::ofstream outFile(argv[2]);
    if(!outFile.good()){
        std::cerr << "Can not open " << argv[2] << " to write!" << std::endl;
        exit(1);
    }

    std::string json_file;
    json_file = std::string(argv[1]);
    int count = 0;

    if(argc >= 4){
        //an exception to ensure the right command is passed to the program
        try{
            if(std::string(argv[3]) == "sound"){
                std::unordered_map<std::string, Sound> sounds;
                create_sound_map(sounds, json_file);
                std::priority_queue<Sound> sound_queue;
                //adding map elements to a proirity queue so they get sorted
                for(std::unordered_map<std::string, Sound>::iterator it = sounds.begin(); it != sounds.end(); ++it) {
                    sound_queue.push(it->second);
                }
                //printint out top 10 sounds
                outFile << "trending sounds:" << std::endl << std::endl;
                while(!sound_queue.empty() && count < 10){
                    outFile << sound_queue.top();
                    sound_queue.pop();
                    count++;
                }
            }else if(std::string(argv[3]) == "hashtag"){
                std::unordered_map<std::string, Hashtag> tags;
                create_hashtag_map(tags, json_file);
                std::priority_queue<Hashtag> tags_queue;
                //adding map elements to a proirity queue so they get sorted
                for(std::unordered_map<std::string, Hashtag>::iterator it = tags.begin(); it != tags.end(); ++it) {
                    tags_queue.push(it->second);
                }
                //prrinting out top 10 hashtags
                outFile << "trending hashtags:" << std::endl << std::endl;
                while(!tags_queue.empty() && count < 10){
                    outFile << tags_queue.top();
                    tags_queue.pop();
                    count++;
                }
            }else{
                throw std::invalid_argument("Invalid argument: " + std::string(argv[3]));
            }
        }catch(const std::invalid_argument& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }else{
        std::cerr << "Requires: 4 arguments" << std::endl;
    }

    outFile.close();
    return 0;
}