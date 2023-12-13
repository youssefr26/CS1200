#include <fstream>
#include <iostream>
#include <cmath>
#include <list>

#include "drivers.h"
#include "riders.h"


int main(int argc, char* argv[]){
    //opening input files
    std::ifstream driverInFile(argv[1]);
    if(!driverInFile.good()){
        std::cerr << "Can't open " << argv[1] << "to read" << std::endl;
        exit(0);
    }
    std::ifstream riderInFile(argv[2]);
    if(!riderInFile.good()){
        std::cerr << "Can't open " << argv[2] << "to read" << std::endl;
        exit(1);
    }

    //opening output files
    std::ofstream messagesOutFile(argv[3]);
    if(!messagesOutFile.good()){
        std::cerr << "Can't open " << argv[3] << "to write" << std::endl;
        exit(2);
    }    
    std::ofstream driverOutFile(argv[4]);
    if(!driverOutFile.good()){
        std::cerr << "Can't open " << argv[4] << "to write" << std::endl;
        exit(2);
    }
    std::ofstream riderOutFile(argv[5]);
    if(!riderOutFile.good()){
        std::cerr << "Can't open " << argv[5] << "to write" << std::endl;
        exit(3);
    }
    //creating lists of drivers and riders
    std::list <Drivers> drivers;
    std::list <Riders> riders;
    driver_read(driverInFile, drivers);
    rider_read(riderInFile, riders);


    //calling functions
    if((std::string(argv[7])) == "request"){
        rider_request(argv[6], riders, drivers, messagesOutFile);
        print_riders(riders, riderOutFile);
        print_driver(drivers, driverOutFile);
    }

    if((std::string(argv[7])) == "cancel"){
        cancel(argv[6], riders, drivers, messagesOutFile);
        print_riders(riders, riderOutFile);
        print_driver(drivers, driverOutFile);
    }


    //closing files
    driverInFile.close();
    riderInFile.close();
    messagesOutFile.close();
    driverOutFile.close();
    riderOutFile.close();


    return 0;
}