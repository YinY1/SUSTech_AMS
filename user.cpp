#include "user.h"
#include "base64.h"
#include "check.h"
#include "control.h"
#include <iostream>

using namespace std;

string user::set_phone_number()
{
    string num;
    cout << "\n[INFO]请输入手机号码：输入0返回\n" << endl;
    while (1)
    {
        cin >> num;
        if(num=="0")
            return "0";
        if(phone_check(num)) break;
    }
    return num;
}

void user::set_name()
{
    string name;
    cout << "\n[INFO]请输入姓名：\n" << endl;
    while (cin >> name)
    {
        if (name.length() < 45)
        {
            strcpy_s(this->name, name.c_str());
            break;
        }
        else
            cout << "\n[WRONG]姓名过长，请重新输入：\n" << endl;
    }
}

void user::set_password()
{
    string password;
    bool check = 0;
    cout << "\n[INFO]请输入密码：\n" << endl;
    while (!check)
    {
        cin>>password;
        check = password_check(password); //检查密码是否合法
    }
    strcpy_s(this->password, password.c_str());
}