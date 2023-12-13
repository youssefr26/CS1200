#ifndef __drivers_h_
#define __drivers_h_

#include <string>
#include <list>
#include <fstream>
#include <iostream>

class Drivers{
public:
//accessors 
std::string get_driver_first_name(){return driver_first_name;}
std::string get_driver_last_name(){return driver_last_name;}
std::string get_driver_vehicle(){return driver_vehicle;}
std::string get_driver_phone(){return driver_phone;}
std::string get_driver_state(){return driver_state;}
double get_driver_rating(){return rating;}
double get_driver_lat(){return current_lat;}
double get_driver_long(){return current_long;}
double get_driver_distance(){return distance;}
std::string get_driver_gender(){return gender;}
int get_driver_age(){return age;}
std::string get_rider_first_name(){return rider_first_name;}
std::string get_rider_last_name(){return rider_last_name;}
std::string get_rider_phone(){return rider_phone;}






//modifiers
void set_driver_first_name(const std::string& name){driver_first_name = name;}
void set_driver_last_name(const std::string& name){driver_last_name = name;}
void set_gender(const std::string& aGender){gender = aGender;}
void set_age(const std::string& aAge){age = stoi(aAge);}
void set_driver_phone(const std::string& aPhone){driver_phone = aPhone;}
void set_rating(const std::string& aRating){rating = stod(aRating);}
void set_current_lat(const std::string& aCurrent_lat){current_lat = stod(aCurrent_lat);}
void set_current_long(const std::string& aCurrent_long){current_long = stod(aCurrent_long);}
void set_driver_vehicle(const std::string& aVehicle){driver_vehicle = aVehicle;}
void set_driver_state(const std::string& aDriver_state){driver_state = aDriver_state;}
void set_rider_first_name(const std::string& aRider_first_name){rider_first_name = aRider_first_name;}
void set_rider_last_name(const std::string& aRider_last_name){rider_last_name = aRider_last_name;}
void set_rider_phone(const std::string& aRider_phone){rider_phone = aRider_phone;}
void set_driver_distance(const double aDistance){distance = aDistance;}

private:
    std::string driver_first_name;
    std::string driver_last_name;
    std::string gender;
    int age;
    std::string driver_phone;
    double rating;
    double current_lat;
    double current_long;
    std::string driver_vehicle;
    std::string driver_state;
    std::string rider_first_name;
    std::string rider_last_name;
    std::string rider_phone;
    double distance;

};

//non-member functions
void driver_read( std::ifstream& driver_file, std::list <Drivers>& driver_list);
void print_driver(std::list<Drivers>& drivers_list, std::ofstream& output_file);
#endif