#include "user.h"
#include "check.h"
#include "menu.h"
using namespace std;

void user::set_name()
{
    string name;
    cout << "请输入姓名：" << endl;
    while(cin >> name)
    {
        if(name.length()<45)
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
    strcpy_s(this->phone_number, num.c_str());
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
    strcpy_s(this->id, id.c_str());
    if (id[17] % 2) //判断性别,身份证第17位为奇数为男，偶数为女
        strcpy_s(this->gender, "男");
    else
        strcpy_s(this->gender, "女");
}