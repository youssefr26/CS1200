#include <string>

using namespace std;


class Course{
public:
Course();
//accessors
int get_crn() const;
string get_department_code() const;
string get_course_code() const;
string get_course_title() const;
string get_days() const;
string get_start_time() const;
string get_end_time() const;
string get_room() const;
int get_first_day() const;
int get_start_time_24() const;
char get_day1() const;
string get_print_day() const;

//modifiers
void set_crn(int aCrn);
void set_department_code(string aDepartment_code);
void set_course_code(string aCourse_code);
void set_course_title(string aCourse_title);
void set_days(string aDays);
void set_start_time(string aStart_time);
void set_end_time(string aEnd_time);
void set_room(string aRoom);
void set_first_day(char aDay);
void set_start_time_24(string aStart_Time_12);
void set_day1(char aDay1);
void set_print_day(char aDay1);











private:
int crn;
string department_code;
string course_code;
string course_title;
string days;
string start_time;
string end_time;
string room;
int first_day;
int start_time_24;
char day1;
string print_day;
};
//non-member functions
bool room_compare(const Course& a, const Course& b);
bool dept_compare(const Course& a, const Course& b);





