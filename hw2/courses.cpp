#include "courses.h"
#include <string>


Course::Course(){

}

int Course::get_crn() const{
    return crn;
}

string Course::get_department_code() const{
    return department_code;
} 

string Course::get_course_code() const{
    return course_code;
}

string Course::get_course_title() const{
    return course_title;
}

string Course::get_days() const{
    return days;
}

string Course::get_start_time() const{
    return start_time;
}

string Course::get_end_time() const{
    return end_time;
}

string Course::get_room() const{
    return room;
}

int Course::get_first_day() const{
    return first_day;
}

int Course::get_start_time_24() const{
    return start_time_24;
}


char Course::get_day1() const{
    return day1;
}

string Course::get_print_day() const{
    return print_day;
}



void Course::set_crn(int aCrn){
    crn = aCrn;
}

void Course::set_department_code(string aDepartment_code){
    department_code = aDepartment_code;
}

void Course::set_course_code(string aCourse_code){
    course_code = aCourse_code;
}

void Course::set_course_title(string aCourse_title){
    course_title = aCourse_title;
}

void Course::set_days(string aDays){
    days = aDays;
}

void Course::set_start_time(string aStart_time){
    start_time = aStart_time;
}

void Course::set_end_time(string aEnd_time){
    end_time = aEnd_time;
}

void Course::set_room(string aRoom){
    room = aRoom;
}

//creating a first day to use for sorting
void Course::set_first_day(char aDay){
    if(aDay=='M'){
        first_day = 0;
    }else if(aDay=='T'){
        first_day = 1;
    }else if(aDay=='W'){
        first_day = 2;
    }else if(aDay=='R'){
        first_day = 3;
    }else if(aDay=='F'){
        first_day = 4;
    }
}

//changing start time into 24hr time for sorting
void Course::set_start_time_24(string aStart_Time_12){
    int thousands;
    int hundreds;
    int tens;
    int ones;
    thousands = 1000 * (aStart_Time_12[0]- '0');
    hundreds = 100 * (aStart_Time_12[1]-'0');
    tens = 10 * (aStart_Time_12[3]-'0');
    ones = (aStart_Time_12[4]-'0');
    if((aStart_Time_12[5] == 'P') && (aStart_Time_12[0])!= '1'){
        thousands += 1000;
        hundreds += 200;
    }
    start_time_24 = (thousands + hundreds + tens + ones);
}

void Course::set_day1(char aDay1){
    day1 = aDay1;
}

void Course::set_print_day(char aDay1){
    if(aDay1=='M'){
        print_day = "Monday";
    }else if(aDay1=='T'){
        print_day = "Tuesday";
    }else if(aDay1=='W'){
        print_day = "Wednesday";
    }else if(aDay1=='R'){
        print_day = "Thursday";
    }else if(aDay1=='F'){
        print_day = "Friday";
    }
}



//sorting helper function for rooms
bool room_compare(const Course& a, const Course& b){
    if(a.get_room() == b.get_room()){
        if(a.get_first_day() == b.get_first_day()){
            if(a.get_start_time_24() == b.get_start_time_24()){
                if(a.get_course_code() == b.get_course_code()){
                    if(a.get_department_code() == b.get_department_code()){
                        return true;
                    }
                    return a.get_department_code() < b.get_department_code();
                }
                return a.get_course_code() < b.get_course_code();
            }
            return a.get_start_time_24() < b.get_start_time_24();
        }
        return a.get_first_day() < b.get_first_day();
    }
    return a.get_room() < b.get_room();
}

//sorting helper function for depts
bool dept_compare(const Course& a, const Course& b){
    if(a.get_course_code() == b.get_course_code()){
        if(a.get_first_day() == b.get_first_day()){
            if(a.get_start_time_24() == b.get_start_time_24()){
                return true;
            }
            return a.get_start_time_24() > b.get_start_time_24();
        }
        return a.get_first_day() < b.get_first_day();
    }
    return a.get_course_code() < b.get_course_code();
}

