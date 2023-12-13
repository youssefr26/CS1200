#ifndef user_h_
#define user_h_

#include <string>
#include <fstream>
#include <iostream>

#include "phoneNums.h"

class User{
    public:
    User* next;
    PhoneNums* head;
    PhoneNums* matches_head;
    User() : next(nullptr), head(nullptr), matches_head(nullptr){}
    ~User();


    //accessors
    std::string get_name() const {return name;}
    int get_age() const {return age;}
    std::string get_gender() const {return gender;}
    std::string get_phone() const {return phone;}
    std::string get_job() const {return job;}
    std::string get_school() const {return school;}
    double get_lat() const {return lat;}
    double get_lng() const {return lng;}
    bool get_prem() const {return prem;}
    int get_max_age() const {return max_age;}
    int get_min_age() const {return min_age;}
    int get_max_dist() const {return max_dist;}
    std::string get_pref() const {return pref;}

    //modifiers
    void set_name(const std::string& aName){name = aName;}
    void set_age(const int aAge){age = aAge;}
    void set_gender(const std::string& aGender){gender = aGender;}
    void set_phone(const std::string& aPhone){phone = aPhone;}
    void set_job(const std::string& aJob){job = aJob;}
    void set_school(const std::string& aSchool){school = aSchool;}
    void set_lat(const double aLat){lat = aLat;}
    void set_lng(const double aLng){lng = aLng;}
    void set_prem(const bool aPrem){prem = aPrem;}
    void set_max_age(const int aMax_age){max_age = aMax_age;}
    void set_min_age(const int aMin_age){min_age = aMin_age;}
    void set_max_dist(const int aMax_dist){max_dist = aMax_dist;}
    void set_pref(const std::string& aPref){pref = aPref;}
    void set_likes(const std::string& aLikes);

    //member functions 
    




    private:
    std::string name;
    int age;
    std::string gender;
    std::string phone;
    std::string job;
    std::string school;
    double lat;
    double lng;
    bool prem;
    int max_age;
    int min_age;
    int max_dist;
    std::string pref;


};

//non-member functions
void push_back(User* &head, User* user);
void create_list(std::ifstream& inFile, User* & head,  std::ofstream& outFile);
void push_back_nums(PhoneNums* & head, std::string& num);
std::ostream& operator<< (std::ostream& os, const User& user);

#endif //user_h_