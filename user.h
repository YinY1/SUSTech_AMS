#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class user
{
protected:
    string name;
    string id;
    string password;
    string phone_number;
    string gender; //性别
    int authority;

public:
    virtual void signup() = 0;
    //virtual void login();
    virtual void show() = 0;
    user();
    user(string name, string password, int authority); //测试用后门
    void set_password();
    void set_phone_number();
    void set_id();
    void set_name();
};

#endif