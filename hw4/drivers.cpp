#include "drivers.h"


//accessors

//modifiers

//member functions

//non-member functions
void driver_read(std::ifstream& driver_file, std::list <Drivers>& driver_list){
    Drivers driver;
    std::string word;
    unsigned int i = 0;
    //looping thhrough each line of the file
    //creating an object for each line
    //with all the given info.
    while(driver_file >> word){
        if(i == 0){
            driver.set_driver_first_name(word);
            i++;
        }
        else if(i == 1){
            driver.set_driver_last_name(word);
            i++;
        }
        else if(i == 2){
            driver.set_gender(word);
            i++;
        }
        else if(i == 3){
            driver.set_age(word);
            i++;
        }
        else if(i == 4){
            driver.set_driver_phone(word);
            i++;
        }
        else if(i == 5){
            driver.set_rating(word);
            i++;
        }
        else if(i == 6){
            driver.set_current_lat(word);
            i++;
        }
        else if(i == 7){
            driver.set_current_long(word);
            i++;
        }
        else if(i == 8){
            driver.set_driver_vehicle(word);
            i++;
        }
        else if(i == 9){
            driver.set_driver_state(word);
            i++;
        }
        else if(i == 10){
            driver.set_rider_first_name(word);
            i++;
        }
        else if(i == 11){
            driver.set_rider_last_name(word);
            i++;
        }
        else if(i == 12){
            driver.set_rider_phone(word);
            i = 0;
            driver_list.push_back(driver);
        }
    }
}

void print_driver(std::list<Drivers>& drivers_list, std::ofstream& output_file){
    //printing out the list of objects
    for(std::list<Drivers>::iterator it = drivers_list.begin(); it != drivers_list.end(); it++){
        output_file << (*it).get_driver_first_name() << ' '
        << (*it).get_driver_last_name() << ' '
        << (*it).get_driver_gender() << ' '
        << (*it).get_driver_age() << ' '
        << (*it).get_driver_phone() << ' '
        << (*it).get_driver_rating() << ' '
        << (*it).get_driver_lat() << ' '
        << (*it).get_driver_long() << ' '
        << (*it).get_driver_vehicle() << ' '
        << (*it).get_driver_state() << ' '
        << (*it).get_rider_first_name() << ' '
        << (*it).get_rider_last_name() << ' '
        << (*it).get_rider_phone() << std::endl;
    }
}