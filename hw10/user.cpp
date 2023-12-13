#include "user.h"

User create_user(std::string& profile, std::string& users_file, std::string& posts_file){
    //go through the user file and find the line matching the profile name
    //create a user object and populate it
    std::ifstream usersFile(users_file);
    if (!usersFile.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            exit(1);
    }
    std::string user_line;
    std::string username;
    User user;
    while (std::getline(usersFile, user_line)) {
        get_user(user_line, username);
        if(username == profile){
            user.set_username(username);
            set_info(user, user_line);
            break;
        }
    }
    // don't need this json file anymore, as the content is read into json_content.
    usersFile.close();
    //go through the posts file and find all the posts
    //by the given user and add them to the user's
    //posts set
    std::ifstream postsFile(posts_file);
    if (!postsFile.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            exit(1);
    }
    std::string post_line;
    while (std::getline(postsFile, post_line)) {
        std::string poster = get_poster(post_line);
        if(poster == username){
            std::string post_id = get_id(post_line);
            (user.get_posts()).insert(post_id);
        }
    }
    // don't need this json file anymore, as the content is read into json_content.
    postsFile.close();
    return user;
}

void get_user(std::string& line, std::string& name){
    //makes the given name into the desired username
    size_t username_found = line.find("\"username\": \"");
    size_t username_end = line.find("\", \"", username_found + 13);
    std::string username = line.substr(username_found + 13, username_end - username_found - 13);
    name = username;
}

void set_info(User& user, std::string& line){
    //isolates the desired feilds from each line of the user file
    //populates the user object with the isolated feilds
    size_t id_found = line.find("\"id\": \"");
    size_t id_end = line.find("\", \"", id_found + 7);
    std::string id = line.substr(id_found + 7, id_end - id_found - 7);
    user.set_id(id);    

    size_t pause_found = line.find("\"pauseAll\": \"");
    size_t pause_end = line.find("\", \"", pause_found + 13);
    std::string pause_all = line.substr(pause_found + 13, pause_end - pause_found - 13);
    if(pause_all == "false"){
        user.set_pause_bool(false);
    }else{
        user.set_pause_bool(true);
    }

    size_t likes_found = line.find("\"likes\": \"");
    size_t likes_end = line.find("\", \"", likes_found + 10);
    std::string likes = line.substr(likes_found + 10, likes_end - likes_found - 10);
    if(likes == "false"){
        user.set_likes_bool(false);
    }else{
        user.set_likes_bool(true);
    }

    size_t tags_found = line.find("\"tags\": \"");
    size_t tags_end = line.find("\", \"", tags_found + 9);
    std::string tags = line.substr(tags_found + 9, tags_end - tags_found - 9);
    if(tags == "false"){
        user.set_tags_bool(false);
    }else{
        user.set_tags_bool(true);
    }

    size_t comments_found = line.find("\"comments\": \"");
    size_t comments_end = line.find("\", \"", comments_found + 13);
    std::string comments = line.substr(comments_found + 13, comments_end - comments_found - 13);
    if(comments == "false"){
        user.set_comments_bool(false);
    }else{
        user.set_comments_bool(true);
    }

    size_t follows_found = line.find("\"newFollowers\": \"");
    size_t follows_end = line.find("\", \"", follows_found + 17);
    std::string follows = line.substr(follows_found + 17, follows_end - follows_found - 17);
    if(follows == "false"){
        user.set_follows_bool(false);
    }else{
        user.set_follows_bool(true);
    }

    size_t message_found = line.find("\"messageRequests\": \"");
    size_t message_end = line.find("\"}", message_found + 20);
    std::string message = line.substr(message_found + 20, message_end - message_found - 20);
    if(message == "false"){
        user.set_message_bool(false);
    }else{
        user.set_message_bool(true);
    }

}

std::string get_poster(std::string& line){
    //returns the posted of a post in the 
    //posts file
    size_t poster_found = line.find("\"ownerUsername\":\"");
    size_t poster_end = line.find("\",\"", poster_found + 17);
    std::string poster = line.substr(poster_found + 17, poster_end - poster_found - 17);
    return poster;
}

std::string get_id(std::string& line){
    //returns the id of a post from the posts file
    size_t id_found = line.find("\"id\":\"");
    size_t id_end = line.find("\",\"", id_found + 6);
    std::string id = line.substr(id_found + 6, id_end - id_found - 6);
    return id;
}
