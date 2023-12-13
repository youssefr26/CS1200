#include <iostream>
#include <cmath>

#include "user.h"


//prototypes
void show_preference(User* user, User* & head, std::ofstream& outFile);
void show_likes(User* user, User* & head, std::ofstream& outFile);
void show_matches(User* user, User* & head, std::ofstream& outFile);
void unmatch(User* user, User* & head, User* other_user, std::ofstream& outFile);
void sort_list(PhoneNums* & matches_head);
double calculateDistance(double lat1, double lon1, double lat2, double lon2);


int main(int argc, char* argv[]){
    //error checking input and output files
    std::ifstream userInFile(argv[1]);
    if(!userInFile.good()){
        std::cerr << "Can't open " << argv[1] << " to read." << std::endl;
        exit(1);
    }
    std::ofstream outFile(argv[2]);
    if(!outFile.good()){
        std::cerr << "Can't open " << argv[2] << " to write." << std::endl;
        exit(2);
    }

    //creating the head pointer
    //to the list of Users
    User* head;
    head = nullptr;
    create_list(userInFile, head, outFile);

    //finding the user with the given phone number
    User* user = nullptr;
    User* temp;
    temp = head;
    while(temp != nullptr){
        if(((*temp).get_phone()) == std::string(argv[3])){
            user = temp;
            break;
        }
        temp = temp->next;
    }

    if((std::string(argv[4])) == "profile"){
        show_preference(user, head, outFile);
    }

    if((std::string(argv[4])) == "like"){
        show_likes(user, head, outFile);
    }

    if((std::string(argv[4])) == "match"){
        show_matches(user, head, outFile);
    }

    if((std::string(argv[4])) == "unmatch"){
        //finding the other user
        User* other_user = nullptr;
        User* temp;
        temp = head;
        while(temp != nullptr){
            if(((*temp).get_phone()) == std::string(argv[5])){
                other_user = temp;
                break;
            }
            temp = temp->next;
        }

        unmatch(user, head, other_user, outFile);
    }


    //deleting dynamically allocated memory
    while(head != nullptr){
        User* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}



void show_preference(User* user, User* & head, std::ofstream& outFile){
    User* temp;
    temp = head;
    double dist;
    bool found;
    found = false;
    //looping through list of users
    //if a user meets all the user's preferences
    //print out the user
    while(temp != nullptr){
        if((*temp).get_phone() != (*user).get_phone()){
        if((((*temp).get_age()) <= ((*user).get_max_age())) && (((*temp).get_age()) >= ((*user).get_min_age()))){
            if((*user).get_pref() == "Both" || (*user).get_pref() == (*temp).get_gender()){
                dist = calculateDistance((*user).get_lat(), (*user).get_lng(), (*temp).get_lat(), (*temp).get_lng());
                    if(dist <= ((*user).get_max_dist())){
                        outFile << (*temp);
                        found = true;
                    }
            }
        }
        }
        temp = temp->next;
    }
    if(found != true){
        outFile << "There are no users matching with your preference at this moment." << std::endl << std::endl;
    }
}


void show_likes(User* user, User* & head, std::ofstream& outFile){
    bool found;
    found = false;
    User* temp;
    temp = head;
    PhoneNums* temp_num;
    if((*user).get_prem() != true){
        outFile << "Only premium users can view who liked you." << std::endl << std::endl;
        return;
    }
    //looping through all users
    while(temp != nullptr){
        temp_num = temp->head;
        //looping through each users likes list
        //if the users number is in the other user's likes list
        //print out that user
        while(temp_num != nullptr){
            if((*user).get_phone() == temp_num->number){
                outFile << (*temp);
                found = true;
            }
            temp_num = temp_num->next;
        }
        temp = temp->next;
    }
    if(found != true){
        outFile << "You have not received any likes so far." << std::endl <<std::endl;
    }
}


void show_matches(User* user, User* & head, std::ofstream& outFile){
    bool found;
    found = false;
    if(user->head->next == nullptr){
        outFile << "You do not have any matches at this moment." << std::endl << std::endl;
        return;
    }
    //create a temp to loop through given users likes
    PhoneNums* temp_like_head;
    temp_like_head = user->head;
    //looping through given users likes
    while(temp_like_head != nullptr){
        //creating a temp to loop through all users
        User* temp_head;
        temp_head = head;
        //looping through all users
        while(temp_head != nullptr){
            if((*temp_head).get_phone() == temp_like_head->number){
                PhoneNums* temp_l;
                temp_l = temp_head->head;
                //looping through user likes
                //adding users to match list if they swiped right on user
                while(temp_l != nullptr){
                    if(temp_l->number == (*user).get_phone()){
                        std::string temp_string = (*temp_head).get_phone();
                        push_back_nums(((*user).matches_head), temp_string);
                        found = true;
                    }
                    temp_l = temp_l->next;
                }
            }
            temp_head = temp_head->next;
        }
        temp_like_head = temp_like_head->next;
    }
    if(found != true){
        outFile << "You do not have any matches at this moment." << std::endl << std::endl;
        return;
    }


    //sorting matches
    sort_list(user->matches_head);
    //printing out the users who matched this user
    PhoneNums* matches_head_temp;
    matches_head_temp = user->matches_head;
    while(matches_head_temp != nullptr){
        User* user_head;
        user_head = head;
        while(user_head != nullptr){
            if((*user_head).get_phone() == matches_head_temp->number){
                outFile << (*user_head);
            }
            user_head = user_head->next;
        }
        matches_head_temp = matches_head_temp->next;
    }
}


void unmatch(User* user, User* & head, User* other_user, std::ofstream& outFile){
    //creating first users matches list
    PhoneNums* temp_like_head;
    temp_like_head = user->head;
    while(temp_like_head != nullptr){
        //creating a temp to loop through all users
        User* temp_head;
        temp_head = head;
        //looping through all users
        while(temp_head != nullptr){
            if((*temp_head).get_phone() == temp_like_head->number){
                PhoneNums* temp_l;
                temp_l = temp_head->head;
                //looping through user likes
                //adding users to match list if they swiped right on user
                while(temp_l != nullptr){
                    if(temp_l->number == (*user).get_phone()){
                        std::string temp_string = (*temp_head).get_phone();
                        push_back_nums(((*user).matches_head), temp_string);
                    }
                    temp_l = temp_l->next;
                }
            }
            temp_head = temp_head->next;
        }
        temp_like_head = temp_like_head->next;
    }
    //sorting matches
    sort_list(user->matches_head);

    //creating second users matches list
    PhoneNums* temp_other_like;
    temp_other_like = other_user->head;
    while(temp_other_like != nullptr){
        //creating a temp to loop through all users
        User* temp_head;
        temp_head = head;
        //looping through all users
        while(temp_head != nullptr){
            if((*temp_head).get_phone() == temp_other_like->number){
                PhoneNums* temp_l;
                temp_l = temp_head->head;
                //looping through user likes
                //adding users to match list if they swiped right on user
                while(temp_l != nullptr){
                    if(temp_l->number == (*other_user).get_phone()){
                        std::string temp_string = (*temp_head).get_phone();
                        push_back_nums(((*other_user).matches_head), temp_string);
                    }
                    temp_l = temp_l->next;
                }
            }
            temp_head = temp_head->next;
        }
        temp_other_like = temp_other_like->next;
    }
    //sorting matches
    sort_list(other_user->matches_head);

    
    //removing users from eahother's matches
    if(user->matches_head->next == nullptr){
        user->matches_head = nullptr;
    }
    PhoneNums* user_matches;
    user_matches = user->matches_head;
    PhoneNums* user_prev;
    user_prev = nullptr;
    while(user_matches != nullptr){
        if(user_matches->number == (*other_user).get_phone()){
            user_prev->next = user_matches->next;
            break;
        }
        user_prev = user_matches;
        user_matches = user_matches->next;
    }

    //deleting the user from the other user's match list 
    if(other_user->matches_head->next == nullptr){
        other_user->matches_head = nullptr;
    }

    PhoneNums* other_user_matches;
    other_user_matches = other_user->matches_head;
    PhoneNums* other_user_prev;
    other_user_prev = nullptr;

    while(other_user_matches != nullptr){
    if(other_user_matches->number == (*user).get_phone()){
        other_user_prev->next = other_user_matches->next;
        break;
    }
    other_user_prev = other_user_matches;
    other_user_matches = other_user_matches->next;
    }

    user_matches = user->matches_head;
    other_user_matches = other_user->matches_head;

    //printing out the users match list
    outFile << (*user).get_name() << "'s match list:" << std::endl << std::endl;
    if(user_matches == nullptr){
        outFile << "You do not have any matches at this moment." << std::endl << std::endl;
    }else{
        User* temp_head;
        while(user_matches != nullptr){
            temp_head = head;
            while(temp_head != nullptr){
                if((*temp_head).get_phone() == user_matches->number){
                    outFile << (*temp_head);
                }
                temp_head = temp_head->next;
            }
            user_matches = user_matches->next;
        }
    }

    outFile << "======" << std::endl << std::endl;

    //printing out the other user's match list
    outFile << (*other_user).get_name() << "'s match list:" << std::endl << std::endl;
    if(other_user_matches == nullptr){
        outFile << "You do not have any matches at this moment." << std::endl << std::endl;
    }else{
        User* temp_head;
        while(other_user_matches != nullptr){
            temp_head = head;
            while(temp_head != nullptr){
                if((*temp_head).get_phone() == other_user_matches->number){
                    outFile << (*temp_head);
                }
                temp_head = temp_head->next;
            }
            other_user_matches = other_user_matches->next;
        }
    }
}


double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}


void sort_list(PhoneNums* & matches_head){
    int comp;
    //checking if list is empty
    if(matches_head->next == nullptr){
        return;
    }else if(matches_head->next->next == nullptr){
        //if the list is only two nodes
        //check if sorted if not
        //swap the two nodes values
        PhoneNums* temp;
        comp = ((matches_head->next)->number).compare((matches_head->next->next)->number);
        if(comp > 0){
            return;
        }else{
            temp = matches_head->next;
            matches_head = matches_head->next->next;
            matches_head->next = temp;
            temp = nullptr;
        }
    }else{
        //if the list is more than two nodes
        //loop through the list and if the next nodes 
        //value is greater swap the two nodes values
        //repeat until list is fully sorted
        bool sorted = false;
        while(sorted == false){
            PhoneNums* first = matches_head;
            PhoneNums* second = matches_head->next;
            sorted = true;
            std::string temp;
            while(second != nullptr){
                comp = (second->number).compare((first->number));
                if(comp < 0){
                    sorted = false;
                    temp = first->number;
                    first->number = (second->number);
                    second->number = temp;
                    first = first->next;
                    second = second->next;
                }else{
                    first = first->next;
                    second = second->next;
                }
            }
        }   
    }
}













