#ifndef USER_H
#define USER_H

#include"control.h"
#include <iostream>
#include <string>

class user
{
protected:
    char phone_number[20]={"nophone"};
    char name[50]={};
    char id[25]={};
    char password[20]={};
    char gender[5]={}; //性别
    int authority=0;

public:
    user(){}
    virtual void signup() = 0;
    // virtual void login();
    virtual void show(int) = 0;
    virtual bool read(char[], int) = 0;
    virtual void write(int) = 0;
    void set_password();
    std::string set_phone_number();
    void set_id();
    void set_name();
    std::string get_phone()
    {
        return phone_number;
    }
};

#endif