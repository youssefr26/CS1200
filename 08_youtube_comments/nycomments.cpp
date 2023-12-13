#include <iostream>
#include <fstream>

#include "comment.h"

std::string create_json(std::string& inputFile);




int main(int argc, char* argv[]){
    //file error checking
    std::ifstream opsFile(argv[2]);
    if(!opsFile.good()){
        std::cerr << "Can not open " << argv[2] << " to read!" << std::endl;
    }
    std::ofstream outFile(argv[3]);
    if(!outFile.good()){
        std::cerr << "Can not open " << argv[3] << " to write!" << std::endl;
    }

    Comment* root = nullptr;

    std::string inputFile = std::string(argv[1]);
    std::string json_content = create_json(inputFile);

    create_tree(opsFile, json_content, root, outFile);
    
    return 0;
}


std::string create_json(std::string& inputFile){
    // assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream jsonFile(inputFile);
    if (!jsonFile.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            exit(1);
    }
    std::string json_content;
    std::string line;
    while (std::getline(jsonFile, line)) {
            json_content += line;
    }
    // don't need this json file anymore, as the content is read into json_content.
    jsonFile.close();
    return json_content;
}