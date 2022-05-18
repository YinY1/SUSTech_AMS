#include "user.h"
#include "base64.h"
#include "check.h"
#include "control.h"
#include <iostream>
using namespace std;

string user::set_phone_number()
{
    string num;
    bool check = 0;
    cout << "请输入手机号码：" << endl;
    while (!check)
    {
        cin >> num;
        check = phone_check(num);
    }
    return num;
}

void user::set_name()
{
    string name;
    cout << "请输入姓名：" << endl;
    while (cin >> name)
    {
        if (name.length() < 45)
        {
            strcpy_s(this->name, name.c_str());
            break;
        }
        else
        {
            cout << "姓名过长，请重新输入：" << endl;
        }
    }
}

void user::set_password()
{
    string password;
    bool check = 0;
    cout << "请输入密码：" << endl;
    while (!check)
    {
        cin.ignore(); //清空输入缓冲区
        getline(cin, password);
        check = password_check(password); //检查密码是否合法
    }
    strcpy_s(this->password, password.c_str());
}

void user::set_province()
{
    string province;
    bool check = 0;
    cout << "请输入省份（地区）：" << endl;
    while (!check)
    {
        cin >> province;
        check = province_check(province); //判断省份是否合法
    }
    strcpy_s(this->province, province.c_str());
}

string user::set_college()
{
    string college;
    bool check = 0;
    cout << "请输入学院：" << endl;
    while (!check)
    {
        cin >> college;
        if (college == "0")
            break;
        check = college_check(college); //判断学院是否合法
    }
    return college;
}

string user::get_phone()
{
    return phone_number;
}

string user::get_name()
{
    return name;
}

string user::get_id()
{
    return id;
}

string user::get_province()
{
    return province;
}

//