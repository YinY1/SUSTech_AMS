#ifndef USER_H
#define USER_H

#include<control.h>
#include <iostream>
#include <string>

class user
{
protected:
    std::string name;
    std::string id;
    std::string password;
    std::string phone_number;
    std::string gender; //性别
    int authority;

public:
    user();
    virtual void signup() = 0;
    // virtual void login();
    virtual void show(int) = 0;
    virtual bool read(char[], int) = 0;
    virtual void write(int) = 0;
    void set_password();
    void set_phone_number();
    void set_id();
    void set_name();
};

#endif