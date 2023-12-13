#ifndef _comment_
#define _comment_

#include <string>
#include <iostream>


class Comment{
public:
//constructor
Comment() : sibling(nullptr), reply(nullptr) {};



//accessors 
std::string get_video_id() const {return video_id;}
std::string get_user() const {return user;}
std::string get_comment_id() const {return comment_id;}
int get_likes() const {return likes;}
int get_replies() const {return replies;}
bool get_is_reply() const {return is_reply;}
std::string get_parrent_comment_id() const {return parent_comment_id;}
std::string get_published_date() const {return published_date;}
std::string get_crawled_date() const {return crawled_date;}
bool get_is_video_owner() const {return is_video_owner;}
std::string get_comment() const {return comment;}
Comment* get_sib() {return sibling;}
Comment* get_reply() {return reply;}

//modifiers
void set_video_id(std::string aVideo_id){video_id = aVideo_id;}
void set_user(std::string aUser){user = aUser;}
void set_comment_id(std::string aComment_id){comment_id = aComment_id;}
void set_likes(int aLikes){likes = aLikes;}
void set_replies(int aReplies){replies = aReplies;}
void add_like(){likes++;}
void add_reply(){replies++;}
void set_is_reply(bool aIs_reply){is_reply = aIs_reply;}
void set_parent_comment_id(std::string aParrent_comment_id){parent_comment_id = aParrent_comment_id;}
void set_published_date(std::string aPublish_date){published_date = aPublish_date;}
void set_crawled_date(std::string aCrawled_date){crawled_date = aCrawled_date;}
void set_is_video_owner(bool aIs_video_owner){is_video_owner = aIs_video_owner;}
void set_comment(std::string aComment){comment = aComment;}
void set_sib(Comment* aSib){sibling = aSib;}
void set_reply(Comment* aReply){reply = aReply;}






private:
std::string video_id;
std::string user;
std::string comment_id;
int likes = 0;
int replies = 0;
bool is_reply;
std::string parent_comment_id = "";
std::string published_date;
std::string crawled_date;
bool is_video_owner;
std::string comment;
Comment* sibling;
Comment* reply;
};

//non-member functions
void comment_reply(Comment*& root, std::string& parent_id, std::string& id, std::string& user, std::string& comment, std::string& json_content);
void video_reply(Comment*& root, std::string& id, std::string& user, std::string& comment);
void like_comment(Comment*& root, std::string& id);
void delete_comment(Comment*& comment);
void display_comment(Comment*& comment, int depth, std::ofstream& outFile);
void display_reply_sibs(Comment* reply);
void create_tree(std::ifstream& opsFile ,std::string& json_content, Comment*& root, std::ofstream& outFile);
Comment* find_comment(Comment* root, std::string& id);
void existing_comment(std::string& json_content, Comment*& root, std::string& id);
void existing_replies(std::string& json_content, Comment* root, std::string& parent_id);








#endif