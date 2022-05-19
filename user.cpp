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