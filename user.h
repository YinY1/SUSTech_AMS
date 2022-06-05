#ifndef USER_H
#define USER_H

#include <cstring>
#include <string>
class user
{
public:
    user() {}
    virtual bool login() = 0;
    virtual void display(int) = 0;
    void set_password();            //设置密码
    void set_name();                //设置姓名
    std::string set_phone_number(); //设置手机号
    std::string get_phone()         //获取手机号
    {
        return phone_number;
    }
    std::string get_name()          //获取姓名
    {
        return name;
    }
    std::string get_id()            //获取身份证
    {
        return id;
    }
    template <typename T>
    bool endmark(T &u)              //判断是否到达结束标志
    {
        return u.get_phone() == "nophone";
    }

protected:
    char phone_number[20] = {"nophone"};
    char name[50] = {};
    char id[25] = {};
    char password[20] = {};
};

#endif