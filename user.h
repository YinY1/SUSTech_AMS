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
    void set_password();                                    //设置密码
    void set_name();                                        //设置姓名
    std::string set_phone_number();                         //设置手机号
    std::string get_phone_number() { return phone_number; } //获取手机号
    std::string get_name() { return name; }                 //获取姓名
    std::string get_id() { return id; }                     //获取身份证
    
	template <typename T>
    bool endmark(T &u) //判断是否读取到文件结束标志
    {
        return u.get_phone_number() == "nophone";
    }//用模板简化操作

protected:
    char phone_number[20] = {"nophone"}; //手机号
    char name[50] = {};                  //姓名
    char id[25] = {};                    //身份证
    char password[20] = {};              //密码
};

#endif