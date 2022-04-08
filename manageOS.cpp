#include "check.h"
#include <fstream>
#include <iostream>
#include <string>
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
    user()
    {
        id = "未填写";
        name = "未填写";
        password = "";
        phone_number = "未填写";
        authority = 0;
    }
    user(string name, string password, int authority) //测试用后门
    {
        this->name = name;
        this->password = password;
        this->authority = authority;
    }
    void set_password();
    void set_phone_number();
    void set_id();
    void set_name()
    {
        cout << "请输入姓名：" << endl;
        cin >> name;
    }
};

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

class student : public user
{
    static int count;        //编号
    string student_number;   //学籍号
    string province;         //省份
    string nation;           //民族
    string political_status; //政治面貌
    string school_name;      //学校名称

public:
    student()
    {
        count++;
        authority = 1;
        province="未填写";
        nation="未填写";
        political_status="未填写";
        school_name="未填写";
    }
    void signup();
    void show();
    void set_province();
    void set_student_number();
    void set_basic_info();
    void set_nation();
    void set_political_status();
    void set_school_name();
};

int student::count = 0;

void student::set_province()
{
    string province;
    bool check = 0;
    cout << "请输入高考省份（地区）：" << endl;
    while (!check)
    {
        cin >> province;
        check = province_check(province); //判断省份是否合法
    }
    this->province = province;
}

void student::set_student_number()
{
    cout << "请输入学籍号：" << endl;
    cin >> student_number;
    cout<<"请再次输入学籍号！一旦确认后无法更改！"<<endl;
    string check;
    cin>>check;
    if(check!=student_number)
    {
        cout<<"输入错误！请重新输入！"<<endl;
        set_student_number();
    }
}

void student::set_nation()
{
    string nation;
    bool check = 0;
    cout << "请输入民族：\n格式：XX族，如“汉族”" << endl;
    while (!check)
    {
        cin >> nation;
        check = nation_check(nation); //判断民族是否合法
    }
    this->nation = nation;
}

void student::set_school_name()
{
    cout << "请输入学校名称：" << endl;
    cin >> school_name;
}

void student::set_political_status()
{
    int num = 0;
    //政治面貌
    const char *p[]={"中共党员","中共预备党员","共青团员","民革党员","民盟盟员","民建会员","民进会员","农工党党员","致公党党员","九三学社社员","台盟盟员","无党派人士","群众"};
    cout<<"请输入政治面貌：\n1.中共党员\t2.中共预备党员\t3.共青团员\t4.民革党员\n5.民盟盟员\t6.民建会员\t7.民进会员\t8.农工党党员\n9.致公党党员\t10.九三学社社员\t11.台盟盟员\t12.无党派人士\t13.群众\n";
    while (cin>>num)
    {
        if (num>0&&num<14)
        {
            political_status = p[num-1];
            break;
        }
        else
            cout<<"输入错误，请重新输入："<<endl;
    }
}

void student::signup()
{
    set_name();
    set_phone_number();
    set_id();
    set_password();
    set_province();
    set_student_number();
    system("cls");
}

void student::set_basic_info()
{
    int select;
    cout << "请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.显示目前信息\n0.退出" << endl;
    while (cin >> select)
    {
        switch (select)
        {
        case 1:
            set_school_name();
            break;
        case 2:
            set_nation();
            break;
        case 3:
            set_political_status();
            break;
        case 4:
            set_province();
            break;
        case 5:
            show();
            break;
        case 0:
            system("cls");
            return;
        default:
            cout << "输入错误，请重新输入" << endl;
            set_basic_info();
            break;
        }
        cout << "请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.显示目前信息\n0.退出" << endl;
    }
    system("cls");
}

void student::show()
{
    cout << "编号：" << count << endl;
    cout << "姓名：" << name << endl;
    cout << "性别：" << gender << endl;
    cout << "学籍号：" << student_number << endl;
    cout << "身份证号码：" << id << endl;
    cout << "高考省份（地区）：" << province << endl;
    cout << "手机号码：" << phone_number << endl;
    cout << "民族：" << nation << endl;
    cout << "政治面貌：" << political_status << endl;
    cout << "学校名称：" << school_name << endl;
}

int main()
{
    student s1;
    s1.signup();
    s1.set_basic_info();
    s1.show();
    system("pause");
    return 0;
}