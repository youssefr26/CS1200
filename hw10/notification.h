#ifndef notification_h
#define notification_h

#include "user.h"

#include <ostream>
#include <fstream>
#include <queue>
#include <stack>
#include <memory>

class Notification{
    protected:
    std::string name;
    std::string command;
    std::string third;

    public:
    //destructor
    virtual ~Notification(){}
    // accessors
    const std::string& get_name() const {return name;}
    const std::string& get_command() const {return command;}
    const std::string& get_third() const {return third;}

    // modifiers
    void set_name(const std::string& aName) {name = aName;}
    void set_command(const std::string& aCommand) {command = aCommand;}
    void set_third(const std::string& aThird) {third = aThird;}

    //member functions
    virtual std::string print() const{
        std::string output = "Notification: " + name + " " + command + " " + third;
        return output;
    }
};

//Like class derived from Notification class
class Like : public Notification{
    std::string print() const{
        std::string output = this->name + " liked your post.\n";
        return output;
    }
};

//Tag class derived from Notification class
class Tag : public Notification{
    std::string print() const{
        std::string output = this->name + " tagged you in a post.\n";
        return output;
    }
};

//Comment class derived from Notification class
class Comment : public Notification{
    std::string print() const{
        std::string output = this->name + " commented on your post.\n";
        return output;
    }
};

//Follow class derived from Notification class
class Follow : public Notification{
    std::string print() const{
        std::string output = this->name + " started following you.\n";
        return output;
    }
};

//Message class derived from Notification class
class Message : public Notification{
    std::string print() const{
        std::string output = this->name + " wants to send you a message.\n";
        return output;
    }
};

//non-member functions
void create_notifications(std::string& events_file, User& user, 
std::queue<Notification*>& aggregates, std::queue<std::string>& outputs);
void add_notifications(Notification* notif,  std::queue<Notification*>& aggregates, std::queue<std::string>& outputs);
#endif
