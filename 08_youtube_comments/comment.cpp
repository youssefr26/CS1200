#include "comment.h"

#include <iostream>
#include <fstream>



void create_tree(std::ifstream& opsFile ,std::string& json_content, Comment*& root, std::ofstream& outFile){
    std::string command, id, parent_id, user, comment;
    while(opsFile >> command){
        if(command == "reply_to_comment" || command == "reply_to_video"){
            if(command == "reply_to_comment"){
                opsFile >> parent_id;
            }
            opsFile >> id;
            opsFile >> user;
            // skip any whitespace to get to the next non-whitespace character
            opsFile >> std::ws;
            // now, read the comment
            if (opsFile.peek() == '"') {
                // if the field starts with a double quote, read it as a whole string
                opsFile.get();  // consume the opening double quote
                std::getline(opsFile, comment, '"');  // read until the closing double quote
                // opsFile >> comment;  // read the quoted field
                if (!comment.empty() && comment.back() == '"') {
                    comment.pop_back();  // remove the closing double quote
                }
            }
        }else{
            opsFile >> id;
        }
        //checking each command to see what functions to call
        if(command == "reply_to_comment"){
            comment_reply(root, parent_id, id, user, comment, json_content);
        }else if(command == "reply_to_video"){
            video_reply(root, id, user, comment);
        }else if(command == "like_comment"){
            like_comment(root, id);
        }else if(command == "display_comment"){
            //prints the given comment out then
            //pases its first reply to the function
            //prints out all subsequest replies and siblings
            Comment* comment = find_comment(root, id);
            outFile << (*comment).get_user() << " "
            << (*comment).get_published_date() << std::endl
            << (*comment).get_comment() << std::endl
            << "\U0001F44D " << (*comment).get_likes() <<std::endl;
            if((*comment).get_replies() > 0){
                outFile << (*comment).get_replies() << " ";
                if((*comment).get_replies() == 1){
                    outFile << "reply" << std::endl;
                }else{
                    outFile << "replies" << std::endl;
                }
            }
            Comment* replies = (*comment).get_reply();
            if(replies != nullptr){
                display_comment(replies, 1, outFile);
            }
        }else if(command == "delete_comment"){
            Comment* comment = find_comment(root, id);
            Comment* reply = (*comment).get_reply();
            delete_comment(reply);
            Comment* temp = comment;
            comment = (*comment).get_sib();
            delete temp;
        }else{
            return;
        }
    }
}



void video_reply(Comment*& root, std::string& id, std::string& user, std::string& comment){
    //checks if tree is empty adds new object to tree as root 
    //if it is empty
    if(root == nullptr){
        root = new Comment();
        (*root).set_comment_id(id);
        (*root).set_user(user);
        (*root).set_comment(comment);
        (*root).set_published_date("0 seconds ago");
        return;
    }else if(((*root).get_sib()) == nullptr){
        //checks if root has any siblings
        //if not add new object as sibling
        Comment* temp = new Comment();
        (*temp).set_comment_id(id);
        (*temp).set_user(user);
        (*temp).set_comment(comment);
        (*temp).set_published_date("0 seconds ago");
        (*root).set_sib(temp);
        temp = nullptr;
        return;
    }else{
        //if there is already a sibling
        //go through all of that siblings, siblings
        //once the end is reached add the new object as a sibling
        Comment* start = (*root).get_sib();
        while(start != nullptr){
            if(((*start).get_sib()) == nullptr){
                Comment* temp = new Comment();
                (*temp).set_comment_id(id);
                (*temp).set_user(user);
                (*temp).set_comment(comment);
                (*temp).set_published_date("0 seconds ago");
                (*start).set_sib(temp);
                temp = nullptr;
                return;
            }
            start = ((*start).get_sib());
        }
    }
}

void comment_reply(Comment*& root, std::string& parent_id, std::string& id, std::string& user, std::string& comment, std::string& json_content){
    //function to handle replies in the second and json files
    size_t found;
    found = parent_id.find(".0");
    if(found == std::string::npos){
        existing_comment(json_content, root, parent_id);
        existing_replies(json_content, root, parent_id);
    }
        //if the parent doesnt have any replies
        //add the new oject as a reply to the parent
        Comment* parent = find_comment(root, parent_id);
        if((*parent).get_reply() == nullptr){
            Comment* temp = new Comment();
            (*temp).set_comment_id(id);
            (*temp).set_user(user);
            (*temp).set_comment(comment);
            (*temp).set_published_date("0 seconds ago");
            (*temp).set_parent_comment_id(parent_id);
            (*parent).set_reply(temp);
            (*parent).add_reply();
            temp = nullptr;
            return;
        }else if((*((*parent).get_reply())).get_sib() == nullptr){
            //if the parent has a reply if the reply doesnt have a sibling
            //add the new object as the reply's sibling
            Comment* temp = new Comment();
            (*temp).set_comment_id(id);
            (*temp).set_user(user);
            (*temp).set_comment(comment);
            (*temp).set_published_date("0 seconds ago");
            (*temp).set_parent_comment_id(parent_id);
            (*((*parent).get_reply())).set_sib(temp);
            (*parent).add_reply();
            temp = nullptr;
            return;
        }else{
            //if the reply already has a sibling
            //go though every sibling's sibling
            //once the end is reached add new object as sibling
            Comment* start;
            start = (*((*parent).get_reply())).get_sib();
            while(start != nullptr){
                if((*start).get_sib() == nullptr){
                    Comment* temp = new Comment();
                    (*temp).set_comment_id(id);
                    (*temp).set_user(user);
                    (*temp).set_comment(comment);
                    (*temp).set_published_date("0 seconds ago");
                    (*temp).set_parent_comment_id(parent_id);
                    (*start).set_sib(temp);
                    (*parent).add_reply();
                    temp = nullptr;
                    return;
                }
                start = (*start).get_sib();
            }
        }
}

void existing_comment(std::string& json_content, Comment*& root, std::string& id){
    //function to find an existing comment in the json file

    //gets the lin in json file where comment id is the same as given id
    std::string search;
    search = "\"comment_id\": \"" + id + "\",";
    size_t found = json_content.find(search);
    size_t line_start = json_content.rfind('{', found);
    size_t line_end = json_content.find('}', found);
    std::string line = json_content.substr(line_start + 1, line_end - line_start - 1);

    //isolate each feild that is needed to populate the comment object
    //user
    size_t user_find = line.find("\"author\": \"");
    size_t user_end = line.find('"', user_find + 11);
    std::string user = line.substr(user_find + 11, user_end-user_find-11);
    //likes
    size_t likes_find = line.find("\"like_count\": ");
    size_t likes_end = line.find(',', likes_find + 14);
    std::string likes_string = line.substr(likes_find + 14, likes_end - likes_find - 14);
    int likes = stoi(likes_string);
    //replies
    size_t reply_find = line.find("\"reply_count\": ");
    size_t reply_end = line.find(',', reply_find + 15);
    std::string reply_string = line.substr(reply_find + 15, reply_end - reply_find - 15);
    int replies = stoi(reply_string);
    //parent comment
    size_t parent_find = line.find("\"parent_comment_id\": ");
    size_t parent_end = line.find(',', parent_find + 21);
    std::string parent_comment_id = line.substr(parent_find + 21, parent_end - parent_find - 21);
    //publish date
    size_t publish_find = line.find("\"published_date\": \"");
    size_t publish_end = line.find("\",", publish_find + 19);
    std::string published_date = line.substr(publish_find + 19, publish_end - publish_find - 19);
    //comment
    size_t comment_find = line.find("\"comment\": \"");
    size_t comment_end = line.find("\"}", comment_find + 12);
    std::string comment = line.substr(comment_find + 12, comment_end - comment_find - 12);
    comment.pop_back();

    //creating the new object
    Comment* temp = new Comment();
    (*temp).set_comment_id(id);
    (*temp).set_user(user);
    (*temp).set_comment(comment);
    (*temp).set_published_date(published_date);
    (*temp).set_parent_comment_id(parent_comment_id);
    (*temp).set_replies(replies);
    (*temp).set_likes(likes);

    //making root the new object if the tree is empty
    if(root == nullptr){
        root = temp;
        temp = nullptr;
        return;
    }else if((*root).get_sib() == nullptr){
        //if the root has no siblings
        //add the new object as a sibling
        (*root).set_sib(temp);
        temp = nullptr;
        return;
    }else{
        //if the root has siblings
        //travel through all siblings till end
        //add new object as the last sibling's sibling
        Comment* start;
        start = (*root).get_sib();
        while(start != nullptr){
            if((*start).get_sib() == nullptr){
                (*start).set_sib(temp);
                return;
            }
            start = (*start).get_sib();
        }
    }
}

void existing_replies(std::string& json_content, Comment* root, std::string& parent_id){
    //function to find all replies to a comment that is in the json file
    Comment* parent = find_comment(root, parent_id);
    std::string search;
    search = "\"parent_comment_id\": \"" + parent_id + "\"";
    size_t found = json_content.find(search);
    while(found != std::string::npos){
        size_t line_start = json_content.rfind('{', found);
        size_t line_end = json_content.find('}', found);
        std::string line = json_content.substr(line_start + 1, line_end - line_start - 1);

        //isolate each feild that is needed to populate the comment object
        //user
        size_t user_find = line.find("\"author\": \"");
        size_t user_end = line.find('"', user_find + 11);
        std::string user = line.substr(user_find + 11, user_end-user_find-11);
        //id
        size_t id_find = line.find("\"comment_id\": \"");
        size_t id_end = line.find('"', id_find + 15);
        std::string id = line.substr(id_find + 15, id_end - id_find - 15);


        //likes
        size_t likes_find = line.find("\"like_count\": ");
        size_t likes_end = line.find(',', likes_find + 14);
        std::string likes_string = line.substr(likes_find + 14, likes_end - likes_find - 14);
        int likes = stoi(likes_string);
        //replies
        size_t reply_find = line.find("\"reply_count\": ");
        size_t reply_end = line.find(',', reply_find + 15);
        std::string reply_string = line.substr(reply_find + 15, reply_end - reply_find - 15);
        int replies = stoi(reply_string);
        //parent comment
        size_t parent_find = line.find("\"parent_comment_id\": ");
        size_t parent_end = line.find(',', parent_find + 21);
        std::string parent_comment_id = line.substr(parent_find + 21, parent_end - parent_find - 21);
        //publish date
        size_t publish_find = line.find("\"published_date\": \"");
        size_t publish_end = line.find("\",", publish_find + 19);
        std::string published_date = line.substr(publish_find + 19, publish_end - publish_find - 19);
        //comment
        size_t comment_find = line.find("\"comment\": \"");
        size_t comment_end = line.find("\"}", comment_find + 12);
        std::string comment = line.substr(comment_find + 12, comment_end - comment_find - 12);
        comment.pop_back();

        //creating the new object
            Comment* temp = new Comment();
            (*temp).set_comment_id(id);
            (*temp).set_user(user);
            (*temp).set_comment(comment);
            (*temp).set_published_date(published_date);
            (*temp).set_parent_comment_id(parent_comment_id);
            (*temp).set_replies(replies);
            (*temp).set_likes(likes);

        //if the parent has no replies add the comment
        if((*parent).get_reply() == nullptr){
            (*parent).set_reply(temp);
            temp = nullptr;
        }else if((*(*parent).get_reply()).get_sib() == nullptr){
            //if the reply has no siblings add the comment
            (*(*parent).get_reply()).set_sib(temp);
            temp = nullptr;
        }else{
            //find the last sibling and add the comment as its sibling
            Comment* start;
            start = (*(*parent).get_reply()).get_sib();
            while(start != nullptr){
                if((*start).get_sib() == nullptr){
                    (*start).set_sib(temp);
                    temp = nullptr;
                    break;
                }
                start = (*start).get_sib();
            }
        }
        found = json_content.find(search, line_end + 1);
    }
}

void like_comment(Comment*& root, std::string& id){
    //adds one like to given comment
    Comment* comment = find_comment(root, id);
    (*comment).add_like();
}

void display_comment(Comment*& comment, int depth, std::ofstream& outFile){
    //takes a comment as an input prints out all of its descendents
    //uses depth to track how many tabs are needed
    //prints each comment/reply to output file
    if(comment == nullptr){
        return;
    }
    for(int i = 1; i <= depth; i++){
        outFile << "    ";
    }
    outFile << (*comment).get_user() << " "
    << (*comment).get_published_date() << std::endl;
    for(int i = 1; i <= depth; i++){
    outFile << "    ";
    }
    outFile << (*comment).get_comment() << std::endl;
    for(int i = 1; i <= depth; i++){
    outFile << "    ";
    }
    outFile << "\U0001F44D " << (*comment).get_likes() <<std::endl;
    if((*comment).get_replies() > 0){
     for(int i = 1; i <= depth; i++){
        outFile << "    ";
    }
        outFile << (*comment).get_replies() << " ";
        if((*comment).get_replies() == 1){
            outFile << "reply" << std::endl;
        }else{
            outFile << "replies" << std::endl;
        }
    }

    Comment* sib = (*comment).get_sib();
    Comment* reply = (*comment).get_reply();
    display_comment(reply, depth+1, outFile);
    display_comment(sib, 1, outFile);
}

void delete_comment(Comment*& comment) {
    if (comment == nullptr) {
        return;
    }

    Comment* reply = (*comment).get_reply();
    Comment* sib = (*comment).get_sib();

    // Recursively delete replies
    delete_comment(reply);
    delete_comment(sib);

    // Delete the current comment
        delete comment;
        comment = nullptr;
}


Comment* find_comment(Comment* root, std::string& id){
    //return a pointer to the branch with the given comment id
    if(root == nullptr){
        return nullptr;
    }
    if((*root).get_comment_id() == id){
        return root;
    }
    Comment* found_reply = find_comment((*root).get_reply(), id);
    if(found_reply != nullptr){
        return found_reply;
    }

    return find_comment((*root).get_sib(), id);
}
