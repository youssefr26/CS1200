#ifndef __riders_h_
#define __riders_h_

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <cmath>
#include "drivers.h"

class Riders{
    public:
    //accessors 
    std::string get_rider_phone_number(){return phone;}
    std::string get_rider_first_name(){return rider_first_name;}
    std::string get_rider_last_name(){return rider_last_name;}
    std::string get_rider_vehicle(){return rider_vehicle;}
    std::string get_rider_state(){return rider_state;}
    std::string get_rider_pickup_loc(){return pickup_loc;}
    std::string get_rider_drop_off_loc(){return drop_off_loc;}
    double get_rider_pickup_lat(){return pickup_lat;}
    double get_rider_pickup_long(){return pickup_long;}
    double get_rider_drop_off_lat(){return drop_off_lat;}
    double get_rider_drop_off_long(){return drop_off_long;}
    std::string get_rider_gender(){return gender;}
    double get_rider_rating(){return rating;}
    int get_rider_age(){return age;}
    std::string get_driver_first_name(){return driver_first_name;}
    std::string get_driver_last_name(){return driver_last_name;}
    std::string get_driver_phone(){return driver_phone;}


    //modifiers
    void set_rider_first_name(const std::string& aRider_first_name){rider_first_name = aRider_first_name;}
    void set_rider_last_name(const std::string& aRider_last_name){rider_last_name = aRider_last_name;}
    void set_rider_gender(const std::string& aGender){gender = aGender;}
    void set_rider_age(const std::string& aAge){age = stoi(aAge);}
    void set_rider_phone(const std::string& aRider_phone){phone = aRider_phone;}
    void set_rider_rating(const std::string& aRider_rating){rating = stod(aRider_rating);}
    void set_pickup_loc(const std::string& aPickup_loc){pickup_loc = aPickup_loc;}
    void set_pickup_lat(const std::string& aPickup_lat){pickup_lat = stod(aPickup_lat);}
    void set_pickup_long(const std::string& aPickup_long){pickup_long = stod(aPickup_long);}
    void set_drop_off_loc(const std::string& aDrop_off_loc){drop_off_loc = aDrop_off_loc;}
    void set_drop_off_lat(const std::string& aDrop_off_lat){drop_off_lat = stod(aDrop_off_lat);}
    void set_drop_off_long(const std::string& aDrop_off_long){drop_off_long = stod(aDrop_off_long);}
    void set_rider_vehicle(const std::string& aRider_vehicle){rider_vehicle = aRider_vehicle;}
    void set_rider_state(const std::string& aRider_state){rider_state = aRider_state;}
    void set_driver_first_name(const std::string& name){driver_first_name = name;}
    void set_driver_last_name(const std::string& name){driver_last_name = name;}
    void set_driver_phone(const std::string& aPhone){driver_phone = aPhone;}

    //member functions
    Drivers* find_driver(std::list <Drivers>& driver_list, Riders& rider);

    private:
    std::string rider_first_name;
    std::string rider_last_name;
    std::string gender;
    int age;
    std::string phone;
    double rating;
    std::string pickup_loc;
    double pickup_lat;
    double pickup_long;
    std::string drop_off_loc;
    double drop_off_lat;
    double drop_off_long;
    std::string rider_vehicle;
    std::string rider_state;
    std::string driver_first_name;
    std::string driver_last_name;
    std::string driver_phone;
};

//non-member functions
void rider_read(std::ifstream& rider_file, std::list <Riders>& rider_list);
void rider_request(const std::string& phone_number, std::list <Riders>& riders_list, std::list <Drivers>& driver_list, 
std::ofstream& message_output_file);
double calculateDistance(double lat1, double lon1, double lat2, double lon2);
void print_riders(std::list<Riders>& riders_list, std::ofstream& output_file);
void cancel(const std::string& phone_number, std::list <Riders>& riders_list, std::list <Drivers>& driver_list, 
std::ofstream& output_file);

#endif