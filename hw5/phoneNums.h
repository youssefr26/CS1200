#ifndef phoneNums_h_
#define phoneNums_h_

#include <string>

class PhoneNums{
    public:
    PhoneNums* next;
    std::string number;

    PhoneNums(std::string num) : next(nullptr), number(num) {}
    PhoneNums() : next(nullptr){}

};
#endif //phoneNums_h_