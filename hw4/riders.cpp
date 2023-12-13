#include "riders.h"

//accessors

//modifiers

//member functions
Drivers* Riders::find_driver(std::list<Drivers>& driver_list, Riders& rider){
    double distance = 0;
    Drivers* closest;
    closest = nullptr;
    double current_dist;
    //looping through a list of Drivers objects
    //checking if their car type matches and they are avaible
    //if they do, calculate the distance from the rider
    //if their distnace is closer than the previous distnace
    //set them as the closest driver
    //return the closest driver
    for(std::list<Drivers>::iterator it = driver_list.begin(); it != driver_list.end(); it++){
        if(((*it).get_driver_vehicle() == rider.get_rider_vehicle()) && ((*it).get_driver_state() == "Available")){
            current_dist = calculateDistance(((*it).get_driver_lat()), ((*it).get_driver_long()),
            rider.get_rider_pickup_lat(),rider.get_rider_pickup_long());
            if(distance == 0){
                distance = current_dist;
                closest = &(*it);
                (*it).set_driver_distance(distance);
            }else if(current_dist < distance){
                distance = current_dist;
                closest = &(*it);
                (*it).set_driver_distance(distance);
            }
        }
    }
    return closest;
}


//non-member functions
void rider_read(std::ifstream& rider_file, std::list <Riders>& rider_list){
    Riders rider;
    std::string word;
    unsigned int i = 0;
    //looping through each line in the input file
    //storing the information in an object
    //adding that object to a list of objects
    while(rider_file >> word){
        if(i==0){
            rider.set_rider_first_name(word);
            i++;
        }
        else if(i==1){
            rider.set_rider_last_name(word);
            i++;
        }
        else if(i==2){
            rider.set_rider_gender(word);
            i++;

        }
        else if(i==3){
            rider.set_rider_age(word);
            i++;

        }
        else if(i==4){
            rider.set_rider_phone(word);
            i++;
        }
        else if(i==5){
            rider.set_rider_rating(word);
            i++;

        }
        else if(i==6){
            rider.set_pickup_loc(word);
            i++;
        }
        else if(i==7){
            rider.set_pickup_lat(word);
            i++;
        }
        else if(i==8){
            rider.set_pickup_long(word);
            i++;

        }
        else if(i==9){
            rider.set_drop_off_loc(word);
            i++;
            
        }
        else if(i==10){
            rider.set_drop_off_lat(word);
            i++;
        }
        else if(i==11){
            rider.set_drop_off_long(word);
            i++;
        }
        else if(i==12){
            rider.set_rider_vehicle(word);
            i++;

        }
        else if(i==13){
            rider.set_rider_state(word);
            i++;
        }
        else if(i==14){
            rider.set_driver_first_name(word);
            i++;
        }
        else if(i==15){
            rider.set_driver_last_name(word);
            i++;
        }
        else if(i==16){
            rider.set_driver_phone(word);
            i = 0;
            rider_list.push_back(rider);
        }
    }
}


void rider_request(const std::string& phone_number, std::list <Riders>& riders_list, std::list <Drivers>& driver_list,
    std::ofstream& output_file){
    //printing the messages for the rider and driver
    bool found = false;
    Drivers* driver;
    if(phone_number.size() != 12){
    output_file << "Phone number is invalid." << std::endl;
    found = true;
    }
    for(std::list<Riders>::iterator it = riders_list.begin(); it != riders_list.end(); it++){
        //looping through the list of riders and checking if the phone number matches
        //if it does and the status is correct
        //print out rider information and look for a driver
        if(((*it).get_rider_phone_number()) == phone_number){
            found = true;
            if(((*it).get_rider_state()) == "Driver_on_the_way"){
                output_file << "You have already requested a ride and your driver is on the way to the pickup location."
                << std::endl;
            }else if(((*it).get_rider_state()) == "During_the_trip"){
                output_file << "You can not request a ride at this moment as you are already on a trip." << std::endl;
            }else{
                std::string filler;
                if((*it).get_rider_vehicle() == "Economy"){
                    filler = "an ";
                }else{
                    filler = "a ";
                }
                output_file << "Ride requested for user " << ((*it).get_rider_first_name())
                << ", looking for " << filler << ((*it).get_rider_vehicle()) << " vehicle." <<std::endl
                << "Pick Up Location: " << ((*it).get_rider_pickup_loc())
                << ", Drop Off Location: " << ((*it).get_rider_drop_off_loc()) << "."
                << std::endl;
                //error checking to make sure a driver is found
                if((*it).find_driver(driver_list, (*it)) == nullptr){
                    output_file << "Sorry we can not find a driver for you at this moment.";
                }else{
                    driver = ((*it).find_driver(driver_list, (*it)));
                    //setting the needed variables of each object to the
                    //rider and driver, respectively, that was found
                    (*driver).set_rider_first_name(((*it).get_rider_first_name()));
                    (*driver).set_rider_last_name(((*it).get_rider_last_name()));
                    (*driver).set_rider_phone(((*it).get_rider_phone_number()));
                    (*driver).set_driver_state("On_the_way_to_pickup");
                    (*it).set_driver_first_name((*driver).get_driver_first_name());
                    (*it).set_driver_last_name((*driver).get_driver_last_name());
                    (*it).set_driver_phone((*driver).get_driver_phone());
                    (*it).set_rider_state("Driver_on_the_way");
                    //printing out the result
                    output_file << "We have found the closest driver " << (*driver).get_driver_first_name()
                    << '(' << (*driver).get_driver_rating() << ')' << " for you." << std::endl
                    << (*driver).get_driver_first_name() << " is now "
                    << (floor((*driver).get_driver_distance() * 10) / 10) << " miles away from you.";
                }
            }
        }
    }
    //error checking to make sure an account was found
    if(found != true){
        output_file << "Account does not exist." << std::endl;
    }
}


// calculate the distance between two coordinates using Haversine formula
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

void print_riders(std::list<Riders>& riders_list, std::ofstream& output_file){
    //looping through the list of riders and printing out each object
    for(std::list<Riders>::iterator it = riders_list.begin(); it != riders_list.end(); it++){
        output_file << (*it).get_rider_first_name() << ' '
        << (*it).get_rider_last_name() << ' '
        << (*it).get_rider_gender() << ' '
        << (*it).get_rider_age() << ' '
        << (*it).get_rider_phone_number() << ' '
        << (*it).get_rider_rating() << ' '
        << (*it).get_rider_pickup_loc() << ' '
        << (*it).get_rider_pickup_lat() << ' '
        << (*it).get_rider_pickup_long() << ' '
        << (*it).get_rider_drop_off_loc() << ' '
        << (*it).get_rider_drop_off_lat() << ' '
        << (*it).get_rider_drop_off_long() << ' '
        << (*it).get_rider_vehicle() << ' '
        << (*it).get_rider_state() << ' '
        << (*it).get_driver_first_name() << ' '
        << (*it).get_driver_last_name() << ' '
        << (*it).get_driver_phone() << std::endl;
    }
}

void cancel(const std::string& phone_number, std::list <Riders>& riders_list, std::list <Drivers>& driver_list, 
std::ofstream& output_file){
    bool found = false;
    std::string phone_num_temp;
    std::list<Riders>::iterator it = riders_list.begin();
    //looping through rider list and check if the phone number matches
    //if it does and the state is correct 
    //remove the rider from the list
    //set the drivers states back to what they would be when they were available
    while(it != riders_list.end()){
        if(((*it).get_rider_phone_number()) == phone_number){
            found = true;
            if(((*it).get_rider_state()) != "Driver_on_the_way"){
                output_file << "You can only cancel a ride request if your driver is currently on the way to the pickup location."
                << std::endl;
                return;
            }else{
                output_file << "Ride request for user " << (*it).get_rider_first_name()
                << " is now canceled by the user.";
                it = riders_list.erase(it);
                for(std::list<Drivers>::iterator it = driver_list.begin(); it != driver_list.end(); it++){
                    if(((*it).get_rider_phone()) == phone_number){
                        (*it).set_rider_first_name("null");
                        (*it).set_rider_last_name("null");
                        (*it).set_rider_phone("null");
                        (*it).set_driver_state("Available");
                    }
                }
            }
        }else{
            it++;
        }
    }
    
    std::list<Drivers>::iterator itr = driver_list.begin();
    while(itr != driver_list.end()){
        //looping through the list of driver and check if the phone number matches
        //if it does and the state is correct
        //set the riders state and driver info back to 
        //what it would be when looking for a ride
        //attempt to find a new driver
        //set the drivers info back to what it would be 
        //when their state was available
        if(((*itr).get_driver_phone()) == phone_number){
            found = true;
            if(((*itr).get_driver_state()) != "On_the_way_to_pickup"){
                output_file << "You can only cancel a ride request if you are currently on the way to the pickup location."
                << std::endl;
                return;
            }else{
                output_file << "Your driver " << (*itr).get_driver_first_name()
                << " has cancelled the ride request. We will now find a new driver for you."
                << std::endl;
                for(std::list<Riders>::iterator it = riders_list.begin(); it != riders_list.end(); it++){
                    if(((*it).get_driver_phone()) == phone_number){
                        (*it).set_rider_state("Ready_to_request");
                        (*it).set_driver_first_name("null");
                        (*it).set_driver_last_name("null");
                        (*it).set_driver_phone("null");
                        phone_num_temp = (*it).get_rider_phone_number();
                    }
                }
                rider_request(phone_num_temp, riders_list, driver_list, output_file);
                (*itr).set_driver_state("Available");
                (*itr).set_rider_first_name("null");
                (*itr).set_rider_last_name("null");
                (*itr).set_rider_phone("null");
            }
            itr++;
        }else{
            itr++;
        }
    }
    //error checking to make sure an account was found
    if(found != true){
        output_file << "Account does not exist." << std::endl;
    }
}