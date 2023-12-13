#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "courses.h"
using namespace std;




int main(int argc, char* argv[]){
    //opening input file and error checking
    ifstream inFile(argv[1]);
    if(!inFile.good()){
        cerr << "Can't open " << argv[1] << " to read!" << endl;
        exit(1);
    }
    //opening output file and error checking
    ofstream outFile(argv[2]);
    if(!outFile.good()){
        cerr << "Can't open " << argv[2] << " to write!" << endl;
        exit(1);
    }
    //creating a vector of objects with the information from each line
    string word;
    vector<Course> courses;
    Course course;
    int i = 0;
    bool empty = true;
    //creating objects and adding them
    //to a vector of objects
    while(inFile >> word){
        empty = false;
        if(i==0){
            course.set_crn(stoi(word));
            i++;
        }else if(i==1){
            course.set_department_code(word);
            i++;
        }else if(i==2){
            course.set_course_code(word);
            i++;
        }else if(i==3){
            course.set_course_title(word);
            i++;
        }else if(i==4){
            course.set_days(word);
            course.set_first_day(word[0]);
            course.set_day1(word[0]);
            course.set_print_day(word[0]);
            i++;
            
        }else if(i==5){
            course.set_start_time((word));
            course.set_start_time_24(word);
            i++;
        }else if(i==6){
            course.set_end_time((word));
            i++;
        }else if(i==7){
            course.set_room(word);
            courses.push_back(course);
            //split the courses into different objects by day
            if((course.get_days()).size() > 1){
                Course new_course;
                for(unsigned int j = 1; j < (course.get_days()).size(); j++){
                new_course.set_crn(course.get_crn());
                new_course.set_department_code(course.get_department_code());
                new_course.set_course_code(course.get_course_code());
                new_course.set_course_title(course.get_course_title());
                new_course.set_day1((course.get_days())[j]);
                new_course.set_first_day((course.get_days())[j]);
                new_course.set_print_day((course.get_days())[j]);
                new_course.set_start_time(course.get_start_time());
                new_course.set_start_time_24(course.get_start_time());
                new_course.set_end_time(course.get_end_time());
                new_course.set_room(course.get_room());
                courses.push_back(new_course);
                }
            }
            i = 0;
        }

    }

    //error checking for empty text file
    if(empty == true){
    outFile << "No data available." << endl;
    inFile.close();
    outFile.close();
    exit(1);
    }

    if(string(argv[3]) == "room"){
        sort(courses.begin(), courses.end(), room_compare);
        if(argc == 4){
            vector<Course> classroom;
            vector<int> title_length_vec;
            vector<int> day_length_vec;
            for(unsigned int i = 0; i < courses.size(); i++){
                //spliting the vector into groups based on classroom
                if(i == 0){
                    classroom.push_back(courses[i]);
                    title_length_vec.push_back((courses[i].get_course_title()).size());
                    day_length_vec.push_back((courses[i].get_print_day()).size());
                }else if(courses[i].get_room() == courses[i-1].get_room()){
                    classroom.push_back(courses[i]);
                    title_length_vec.push_back((courses[i].get_course_title()).size());
                    day_length_vec.push_back((courses[i].get_print_day()).size());
                }else{
                    int title_length = *max_element(title_length_vec.begin(), title_length_vec.end());
                    int day_length = *max_element(day_length_vec.begin(), day_length_vec.end());
                    if(classroom.size() == 1){
                        title_length = (classroom[0].get_course_title()).size();
                        day_length = (classroom[0].get_print_day()).size();
                    }
                    if(title_length < 11){
                        title_length = 11;
                    }
                    outFile << "Room " << classroom[0].get_room() << endl;;
                    outFile << "Dept  " << "Coursenum  " << setw(title_length) << left << "Class Title" << "  "
                    << setw(day_length) << left << "Day" << "  " << "Start Time  " << "End Time" << endl;
                    outFile << string(4,'-') << "  " << string(9,'-') << "  " << string(title_length, '-') << "  "
                    << string(day_length,'-') << "  " << string(10,'-') << "  " << string(8,'-') << endl;
                    for(unsigned int j = 0; j < classroom.size(); j++){
                        outFile << classroom[j].get_department_code() << "  " << classroom[j].get_course_code() << "    "
                        << setw(title_length) << left << classroom[j].get_course_title() << "  "
                        << setw(day_length) << left << classroom[j].get_print_day() << "  "
                        << classroom[j].get_start_time() << "     " << classroom[j].get_end_time() << " " << endl;
                    }
                    outFile << classroom.size() << " " << "entries" << endl << endl;

                    classroom.clear();
                    title_length_vec.clear();
                    day_length_vec.clear();
                    classroom.push_back(courses[i]);
                    title_length_vec.push_back((courses[i].get_course_title()).size());
                    day_length_vec.push_back((courses[i].get_print_day()).size());

                }
                }
                    int title_length = *max_element(title_length_vec.begin(), title_length_vec.end());
                    int day_length = *max_element(day_length_vec.begin(), day_length_vec.end());
                    outFile << "Room " << classroom[0].get_room() << endl;;
                    outFile << "Dept  " << "Coursenum  " << setw(title_length) << left << "Class Title" << "  "
                    << setw(day_length) << left << "Day" << "  " << "Start Time  " << "End Time" << endl;
                    outFile << string(4,'-') << "  " << string(9,'-') << "  " << string(title_length, '-') << "  "
                    << string(day_length,'-') << "  " << string(10,'-') << "  " << string(8,'-') << endl;
                    for(unsigned int j = 0; j < classroom.size(); j++){
                        outFile << classroom[j].get_department_code() << "  " << classroom[j].get_course_code() << "    "
                        << setw(title_length) << left << classroom[j].get_course_title() << "  "
                        << setw(day_length) << left << classroom[j].get_print_day() << "  "
                        << classroom[j].get_start_time() << "     " << classroom[j].get_end_time() << " " << endl;
                    }
                    outFile << classroom.size() << " " << "entries" << endl << endl;
                    
            }else if(argc == 5){
            string room_name = string(argv[4]);
            bool matching = false;
            for(unsigned int i = 0; i < courses.size(); i++){
                if(courses[i].get_room() == room_name){
                    matching = true;
                    break;
                }
            }
            if(matching == false){
                outFile << "No data avaiable." << endl;
                inFile.close();
                outFile.close();
                exit(1);
            }
            vector<Course> classroom;
            vector<int> title_length_vec;
            vector<int> day_length_vec;
            for(unsigned int i = 0; i < courses.size(); i++){
                if(courses[i].get_room() == room_name){
                    classroom.push_back(courses[i]);
                    title_length_vec.push_back((courses[i].get_course_title()).size());
                    day_length_vec.push_back((courses[i].get_print_day()).size());
                }

            }
            int title_length = *max_element(title_length_vec.begin(), title_length_vec.end());
            int day_length = *max_element(day_length_vec.begin(), day_length_vec.end());
            outFile << "Room " << classroom[0].get_room() << endl;
            outFile << "Dept  " << "Coursenum  " << setw(title_length) << left << "Class Title" << "  "
            << setw(day_length) << left << "Day" << "  " << "Start Time  " << "End Time" << endl;
            outFile << string(4,'-') << "  " << string(9,'-') << "  " << string(title_length, '-') << "  "
            << string(day_length,'-') << "  " << string(10,'-') << "  " << string(8,'-') << endl;
            for(unsigned int i = 0; i < classroom.size(); i++){
                outFile << classroom[i].get_department_code() << "  " << classroom[i].get_course_code() << "    "
                << setw(title_length) << left << classroom[i].get_course_title() << "  "
                << setw(day_length) << left << classroom[i].get_print_day() << "  "
                << classroom[i].get_start_time() << "     " << classroom[i].get_end_time() << " " << endl;
            }
            outFile << classroom.size() << " " << "entries" << "\n" << "\n" << endl;

        }
        }
        else if(string(argv[3]) == "dept"){
            sort(courses.begin(), courses.end(), dept_compare);
            string dept_name = string(argv[4]);
            bool matching = false;
            for(unsigned int i = 0; i < courses.size(); i++){
                if(courses[i].get_department_code() == dept_name){
                matching = true;
                break;
                }
            }
            if(matching == false){
                outFile << "No data available." << endl;
                inFile.close();
                outFile.close();
                exit(1);
            }
            vector<Course> dept;
            vector<int> title_length_vec;
            vector<int> day_length_vec;
            for(unsigned int i = 0; i < courses.size(); i++){
                if(courses[i].get_department_code() == dept_name){
                    dept.push_back(courses[i]);
                    title_length_vec.push_back((courses[i].get_course_title()).size());
                    day_length_vec.push_back((courses[i].get_print_day()).size());
                }
            }
            //printing the last element of the vector
            int title_length = *max_element(title_length_vec.begin(), title_length_vec.end());
            int day_length = *max_element(day_length_vec.begin(), day_length_vec.end());
            outFile << "Dept " << dept[0].get_department_code() << endl;
            outFile <<  "Coursenum  " << setw(title_length) << left << "Class Title" << "  "
            << setw(day_length) << left << "Day" << "  " << "Start Time  " << "End Time" << endl;
            outFile << string(9,'-') << "  " << string(title_length, '-') << "  "
            << string(day_length,'-') << "  " << string(10,'-') << "  " << string(8,'-') << endl;
            for(unsigned int i = 0; i < dept.size(); i++){
                outFile << dept[i].get_course_code() << "    "
                << setw(title_length) << left << dept[i].get_course_title() << "  "
                << setw(day_length) << left << dept[i].get_print_day() << "  "
                << dept[i].get_start_time() << "     " << dept[i].get_end_time() << " " << endl;
            }
            outFile << dept.size() << " " << "entries" << endl << "\n";

        }else if(string(argv[3]) == "custom"){
            int monday = 0;
            int tuesday = 0;
            int wednesday = 0;
            int thursday = 0;
            int friday = 0;
            int mon_max = 0;
            int tues_max = 0;
            int wedns_max = 0;
            int thurs_max = 0;
            int fri_max = 0;
            string m_max;
            string tu_max;
            string w_max;
            string th_max;
            string f_max;
            string current;
            outFile << "Custom Stat" << endl;
            sort(courses.begin(), courses.end(), room_compare);
            current = courses[0].get_room();
            for(unsigned int i = 0; i < courses.size(); i++){
                if(courses[i].get_room() != current || ((i+1) == courses.size())){
                    if(monday > mon_max){
                        mon_max = monday;
                        m_max = current;
                    }
                    if(tuesday > tues_max){
                        tues_max = tuesday;
                        tu_max = current;
                    }
                     if(wednesday > wedns_max){
                        wedns_max = wednesday;
                        w_max = current;
                    }
                     if(thursday > thurs_max){
                        thurs_max = thursday;
                        th_max = current;
                    }
                     if(friday > fri_max){
                        fri_max = friday;
                        f_max = current;
                    }
                    monday =0;
                    tuesday =0;
                    wednesday=0;
                    thursday = 0; 
                    friday = 0;
                    current = courses[i].get_room();
                }else{
                    if(courses[i].get_print_day() == "Monday"){
                        monday += 1;
                    }else if(courses[i].get_print_day() == "Tuesday"){
                        tuesday += 1;
                    }else if(courses[i].get_print_day() == "Wednesday"){
                        wednesday += 1;
                    }else if(courses[i].get_print_day() == "Thursday"){
                        thursday += 1;
                    }else if(courses[i].get_print_day() == "Friday"){
                        friday += 1;
                    }
                }

            }

            outFile << "The busiest classroom on Monday is " << m_max << " with " << mon_max << " classes." << endl;
            outFile << "The busiest classroom on Tuesday is " << tu_max << " with " << tues_max << " classes." << endl;
            outFile << "The busiest classroom on Wednesday is " << w_max << " with " << wedns_max << " classes." << endl;
            outFile << "The busiest classroom on Thursday is " << th_max << " with " << thurs_max << " classes." << endl;
            outFile << "The busiest classroom on Friday is " << f_max << " with " << fri_max << " classes." << endl;


        }

    //closing files
    inFile.close();
    outFile.close();

    return 0;    
    }
