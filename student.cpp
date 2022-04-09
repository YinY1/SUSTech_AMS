#include "student.h"
#include "check.h"
student::student()
{
    count++;
    authority = 1;
    province = "未填写";
    nation = "未填写";
    political_status = "未填写";
    school_name = "未填写";
}

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
    cout << "\n请输入学籍号：" << endl;
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
    cout << "\n请输入民族：\n格式：XX族，如“汉族”" << endl;
    while (!check)
    {
        cin >> nation;
        check = nation_check(nation); //判断民族是否合法
    }
    this->nation = nation;
}

void student::set_school_name()
{
    cout << "\n请输入学校名称：" << endl;
    cin >> school_name;
}

void student::set_political_status()
{
    int num = 0;
    //政治面貌
    const char *p[]={"中共党员","中共预备党员","共青团员","民革党员","民盟盟员","民建会员","民进会员","农工党党员","致公党党员","九三学社社员","台盟盟员","无党派人士","群众"};
    cout<<"\n请输入政治面貌：\n1.中共党员\t2.中共预备党员\t3.共青团员\t4.民革党员\n5.民盟盟员\t6.民建会员\t7.民进会员\t8.农工党党员\n9.致公党党员\t10.九三学社社员\t11.台盟盟员\t12.无党派人士\t13.群众\n";
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
    cls();
}

void student::set_basic_info()
{
    int select;
    cout << "\n请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.显示目前信息\n0.退出" << endl;
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
            cls();
            return;
        default:
            cout << "输入错误，请重新输入" << endl;
            set_basic_info();
            break;
        }
        cout << "\n请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.显示目前信息\n0.退出\n" << endl;
    }
    cls();
}

void student::show()
{
    cout << "\n编号：" << count << endl;
    cout << "姓名：" << name << endl;
    cout << "性别：" << gender << endl;
    cout << "学籍号：" << student_number << endl;
    cout << "身份证号码：" << id << endl;
    cout << "高考省份（地区）：" << province << endl;
    cout << "手机号码：" << phone_number << endl;
    cout << "民族：" << nation << endl;
    cout << "政治面貌：" << political_status << endl;
    cout << "学校名称：" << school_name <<"\n"<< endl;
}