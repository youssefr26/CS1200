#include "user.h"

//accessors

//modifiers

//member functions
User::~User(){
    //destructor to delete all the memory
    //allocated when creatin phone number lists
    while(head != nullptr){
        PhoneNums* temp = head;
        head = head->next;
        delete temp;
    }

    while(matches_head != nullptr){
        PhoneNums* temp = matches_head;
        matches_head = matches_head->next;
        delete temp;
    }
}

//non-member functions
void create_list(std::ifstream& inFile, User* & head, std::ofstream& outFile){
    //function to create each User object
    User* temp;
    std::string word;
    unsigned int i = 0;
    //loop though each line in the input file
    while(inFile >> word){
        if(i == 0){
            temp = new User;
            (*temp).set_name(word);
            i++;
        }else if(i == 1){
            (*temp).set_age(stoi(word));
            i++;
        }else if(i == 2){
            (*temp).set_gender(word);
            i++;
        }else if(i == 3){
            (*temp).set_phone(word);
            i++;
        }else if(i == 4){
            (*temp).set_job(word);
            i++;
        }else if(i == 5){
            (*temp).set_school(word);
            i++;
        }else if(i == 6){
            (*temp).set_lat(stod(word));
            i++;
        }else if(i == 7){
            (*temp).set_lng(stod(word));
            i++;
        }else if(i == 8){
            if(word == "false"){
                (*temp).set_prem(false);
            }else{
                (*temp).set_prem(true);
            }
            i++;
        }else if(i == 9){
            (*temp).set_min_age(stoi(word));
            i++;
        }else if(i == 10){
            (*temp).set_max_age(stoi(word));
            i++;
        }else if(i == 11){
            (*temp).set_max_dist(stoi(word));
            i++;
        }else if(i == 12){
            (*temp).set_pref(word);
            i++;
        }else if (i == 13){
            if(word == "null"){
            push_back_nums(((*temp).head), word);
            }else{
                //break up the big phone number string 
                //into individual phone nums
                std::string temp_string;
                for(unsigned int i = 0; i < word.size(); i++){
                    if(word[i] != '_'){
                        temp_string += word[i];
                    }else{
                        push_back_nums(((*temp).head), temp_string);
                        temp_string.clear();
                    }
                }
                if(!temp_string.empty()){
                    push_back_nums(((*temp).head), temp_string);
                    temp_string.clear();
                }
            }
            push_back(head, temp);
            i = 0;
        }
    }
}


void push_back(User* &head, User* user){
    //pushes the user object to the end
    //of the linked list
    if(head == nullptr){
    user->next = nullptr;
    head = user;
    }else{
        push_back(head->next, user);
    }
}

void push_back_nums(PhoneNums* & head, std::string& num){
    //function to create phone number lists
    if(head == nullptr){
        PhoneNums* temp = new PhoneNums;
        temp->number = num;
        temp->next = head;
        head = temp;
    }else{
        push_back_nums(head->next, num);
    }
}

std::ostream& operator<<(std::ostream& os, const User& user){
    os << user.get_name() << ' '
    <<user.get_age() << std::endl;
    if(user.get_job() != "Undisclosed"){
        std::string temp;
        std::string word;
        word = user.get_job();
        //getting rid of the underscores in job name
        for(unsigned int i = 0; i < word.size(); i++){
            if(word[i] == '_'){
                os << temp << ' ';
                temp.clear();
            }else{
                temp += word[i];
            }
        }
        if(!temp.empty()){
            os << temp;
        }
        os << std::endl;
    }
    //getting rid of the underscores in school name
    if(user.get_school() != "Undisclosed"){
        std::string temp;
        std::string word;
        word = user.get_school();
        for(unsigned int i = 0; i < word.size(); i++){
            if(word[i] == '_'){
                os << temp << ' ';
                temp.clear();
            }else{
                temp += word[i];
            }
        }
        if(!temp.empty()){
            os << temp;
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}
