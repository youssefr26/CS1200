#ifndef user_h
#define user_h

#include <string>
#include <set>
#include <fstream>
#include <iostream>

class User{
    public:
    //modifiers
    void set_pause_bool(const bool aBool){pause_all = aBool;}
    void set_likes_bool(const bool aBool){likes_bool = aBool;}
    void set_tags_bool(const bool aBool){tags_bool = aBool;}
    void set_comments_bool(const bool aBool){comments_bool = aBool;}
    void set_follows_bool(const bool aBool){follows_bool = aBool;}
    void set_message_bool(const bool aBool){message_bool = aBool;}
    void set_id(const std::string& aId){id = aId;}
    void set_username(const std::string& aUsername){username = aUsername;}

    //accesors
    bool get_pause_bool()const {return pause_all;}
    bool get_likes_bool()const {return likes_bool;}
    bool get_tags_bool()const {return tags_bool;}
    bool get_comments_bool()const {return comments_bool;}
    bool get_follows_bool()const {return follows_bool;}
    bool get_message_bool()const {return message_bool;}
    std::string get_id()const {return id;}
    std::string get_username()const {return username;}
    std::set<std::string>& get_posts(){return posts;}

    private:
    bool pause_all;
    bool likes_bool;
    bool tags_bool;
    bool comments_bool;
    bool follows_bool;
    bool message_bool;
    std::string id;
    std::string username;
    std::set<std::string> posts;
};

//non-member functions
User create_user(std::string& profile, std::string& users_file, std::string& posts_file);
void get_user(std::string& line, std::string& name);
void set_info(User& user, std::string& line);
std::string get_poster(std::string& line);
std::string get_id(std::string& line);
#endif
