#include "user.h"
#include "check.h"
#include "menu.h"
using namespace std;
user::user()
{
    id = "未填写";
    name = "未填写";
    password = "";
    phone_number = "未填写";
    authority = 0;
}

void user::set_name()
{
    cout << "请输入姓名：" << endl;
    cin >> name;
}

void user::set_phone_number()
{
    string num;
    bool check = 0;
    cout << "请输入手机号码：\n(手机号码作为登录和找回密码的依据)" << endl;
    while (!check)
    {
        cin >> num;
        check = phone_check(num);
    }
    this->phone_number = num;
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
    this->password = password;
}

void user::set_id()
{

    string id;
    bool check = 0;
    cout << "请输入身份证号码：" << endl;
    while (!check)
    {
        cin >> id;
        check = id_check(id); //判断身份证号码是否合法
    }
    this->id = id;
    if (id[17] % 2) //判断性别,身份证第17位为奇数为男，偶数为女
        gender = "男";
    else
        gender = "女";
}