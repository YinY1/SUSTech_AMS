#include "student.h"
#include "base64.h"
#include "check.h"

//后包含windows.h会导致byte重定义,命名空间std会被重复包含https://github.com/msys2/MINGW-packages/issues/7035
//所以不要在头文件using,实在不想打std::可以在cpp里面using，尽量不要using namespace，除非确定没有重复。
using namespace std;

student::student()
{
    authority = 1;
    province = "";
    nation = "";
    political_status = "";
    school_name = "";
    dad_name = "";
    mom_name = "";
    dad_phone_number = "";
    mom_phone_number = "";
    dad_job = "";
    mom_job = "";
    dad_work_address = "";
    mom_work_address = "";
}

const student_dat mark = {"nophone", "\0", "\0", "\0", "\0", "\0", "\0", "\0"};

void student::signup()
{
    char key[15];
    set_phone_number();
    strcpy_s(key, phone_number.c_str());
    //查重
    if (read(key, 0))
    {
        cout << "用户已存在！" << endl;
        return;
    }
    else
    {
        write(0);
    }
}

bool student::login()
{
    char key[15];
    cout << "请输入手机号：\t 输入0返回" << endl;
    while (cin >> key)
    {
        if (key[0] == '0')
        {
            return 0;
        }
        if (read(key, 1))
        {
            sleep();
            cls();
            cout << "欢迎" << name << endl;
            return 1;
        }
        else
        {
            cout << "用户不存在！请重新输入账号！\t输入0返回" << endl;
        }
    }
    return 0;
}

void student::set_parents_info()
{
    cout << "\n请选择需要填写的信息：\n"
         << "1.父亲信息\t2.母亲信息\t3.父亲联系方式\t4.母亲联系方式\n"
         << "5.父亲工作地址\t6.母亲工作地址\t7.父亲职业\t8.母亲职业\t9.显示家长信息\n0.返回" << endl;
    int choice;
    while (cin >> choice)
    {
        switch (choice)
        {
        case 1:
            cout << "请输入父亲姓名：" << endl;
            cin >> dad_name;
            break;
        case 2:
            cout << "请输入母亲姓名：" << endl;
            cin >> mom_name;
            break;
        case 3:
            cout << "请输入父亲联系方式：" << endl;
            cin >> dad_phone_number;
            break;
        case 4:
            cout << "请输入母亲联系方式：" << endl;
            cin >> mom_phone_number;
            break;
        case 5:
            cout << "请输入父亲工作地址：" << endl;
            cin >> dad_work_address;
            break;
        case 6:
            cout << "请输入母亲工作地址：" << endl;
            cin >> mom_work_address;
            break;
        case 7:
            cout << "请输入父亲职业：" << endl;
            cin >> dad_job;
            break;
        case 8:
            cout << "请输入母亲职业：" << endl;
            cin >> mom_job;
            break;
        case 9:
            show(1);
            pause();
            break;
        case 0:
            write(1);
            cls();
            return;
        default:
            cout << "\n输入错误！请重新输入！" << endl;
            break;
        }
        cout << "\n请选择需要填写的信息：\n"
                 << "1.父亲信息\t2.母亲信息\t3.父亲联系方式\t4.母亲联系方式\n"
                 << "5.父亲工作地址\t6.母亲工作地址\t7.父亲职业\t8.母亲职业\t9.显示家长信息\n0.返回"
                 << endl;
    }
}

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
    cout << "请再次输入学籍号！一旦确认后无法更改！" << endl;
    string check;
    cin >> check;
    if (check != student_number)
    {
        cout << "输入错误！请重新输入！" << endl;
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
    const char *p[] = {"中共党员", "中共预备党员", "共青团员", "民革党员", "民盟盟员", "民建会员", "民进会员", "农工党党员", "致公党党员", "九三学社社员", "台盟盟员", "无党派人士", "群众"};
    cout << "\n请输入政治面貌：\n1.中共党员\t2.中共预备党员\t3.共青团员\t4.民革党员\n5.民盟盟员\t6.民建会员\t7.民进会员\t8.农工党党员\n9.致公党党员\t10.九三学社社员\t11.台盟盟员\t12.无党派人士\t13.群众\n";
    while (cin >> num)
    {
        if (num > 0 && num < 14)
        {
            political_status = p[num - 1];
            break;
        }
        else
            cout << "输入错误，请重新输入：" << endl;
    }
}

void student::set_basic_info()
{
    int select;
    cout << "\n请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.学籍号\n6.身份证\n7.显示目前信息\n0.退出" << endl;
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
            set_student_number();
            break;
        case 6:
            set_id();
            break;
        case 7:
            show(0);
            break;
        case 0:
            cls();
            return;
        default:
            cout << "输入错误，请重新输入" << endl;
            set_basic_info();
            break;
        }
        cout << "\n请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.学籍号\n6.身份证\n7.显示目前信息\n0.退出\n"
             << endl;
    }
    cls();
}

void student::show(int choice)
{
    switch (choice)
    {
    case 0:
        cout << "\n姓名：" << name
             << "\n性别：" << gender
             << "\n学籍号：" << student_number
             << "\n身份证号码：" << id
             << "\n高考省份（地区）：" << province
             << "\n手机号码：" << phone_number
             << "\n民族：" << nation
             << "\n政治面貌：" << political_status
             << "\n学校名称：" << school_name << "\n"
             << endl;
        break;
    case 1:
        cout << "\n父亲姓名:" << dad_name
             << "\n父亲电话:" << dad_phone_number
             << "\n父亲职业:" << dad_job
             << "\n父亲工作地址:" << dad_work_address
             << "\n母亲姓名:" << mom_name
             << "\n母亲电话:" << mom_phone_number
             << "\n母亲职业:" << mom_job
             << "\n母亲工作地址:" << mom_work_address
             << endl;
        break;
    }
}

bool student::read(char key[], int choice)
{
    student_dat r;
    fstream f("stu.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    do
    {
        f.read((char *)&r, sizeof(student_dat));
    } while (strcmp(key, r.phone_number) && !endmark(r));
    if (strcmp(key, r.phone_number))
    {
        f.close();
        return 0; //没有重复
    }
    switch (choice)
    {
    case 0: //用作注册时单纯查询账号
        break;
    case 1: //用作登录时同时检查密码
    {
        string pass;
        cout << "\n请输入密码：" << endl;
        while (cin >> pass)
        {
            if (strcmp(base64_encode(pass).c_str(), r.password) == 0)
            {
                cout << "\n登录成功！" << endl;
                //登录后读取用户信息
                id = base64_decode(r.id);
                student_number = base64_decode(r.student_number);
                province = base64_decode(r.province);
                nation = base64_decode(r.nation);
                political_status = base64_decode(r.political_status);
                school_name = base64_decode(r.school_name);
                name = base64_decode(r.name);
                password = pass;
                phone_number = r.phone_number;
                dad_name = base64_decode(r.dad_name);
                dad_phone_number = base64_decode(r.dad_phone_number);
                dad_job = base64_decode(r.dad_job);
                dad_work_address = base64_decode(r.dad_work_address);
                mom_name = base64_decode(r.mom_name);
                mom_phone_number = base64_decode(r.mom_phone_number);
                mom_job = base64_decode(r.mom_job);
                mom_work_address = base64_decode(r.mom_work_address);
                break;
            }
            cout << "\n密码错误，请重新输入：" << endl;
        }
        break;
    }
    }
    f.close();
    return 1;
}

void student::write(int choice)
{
    student_dat w;
    fstream f("stu.dat", ios::in | ios::out | ios::binary);
    f.seekp(0, ios::beg);
    switch (choice)
    {
    case 0: //注册
    {
        do
        {
            f.read((char *)&w, sizeof(student_dat));
        } while (!endmark(w));
        f.seekp(-long(sizeof(student_dat)), ios::cur);
        set_name();
        set_password();
        set_basic_info();
        //用base64简单加密了一下
        strcpy_s(w.name, base64_encode(name).c_str());
        strcpy_s(w.password, base64_encode(password).c_str());
        strcpy_s(w.phone_number, phone_number.c_str());
        strcpy_s(w.province, base64_encode(province).c_str());
        strcpy_s(w.nation, base64_encode(nation).c_str());
        strcpy_s(w.political_status, base64_encode(political_status).c_str());
        strcpy_s(w.school_name, base64_encode(school_name).c_str());
        strcpy_s(w.student_number, base64_encode(student_number).c_str());
        strcpy_s(w.id, base64_encode(id).c_str());
        f.write((char *)&w, sizeof(student_dat));
        f.write((char *)&mark, sizeof(student_dat));
        cout << "注册成功" << endl;
        break;
    }
    case 1: //写家长信息
    {
        do
        {
            f.read((char *)&w, sizeof(student_dat));
        } while (strcmp(phone_number.c_str(), w.phone_number));
        //置写指针位置，设置错误会覆盖信息
        f.seekp(-long(sizeof(student_dat)), ios::cur);
        strcpy_s(w.dad_name, base64_encode(dad_name).c_str());
        strcpy_s(w.dad_phone_number, base64_encode(dad_phone_number).c_str());
        strcpy_s(w.mom_name, base64_encode(mom_name).c_str());
        strcpy_s(w.mom_phone_number, base64_encode(mom_phone_number).c_str());
        strcpy_s(w.dad_work_address, base64_encode(dad_work_address).c_str());
        strcpy_s(w.mom_work_address, base64_encode(mom_work_address).c_str());
        f.write((char *)&w, sizeof(student_dat));
        cout << "家长信息写入成功" << endl;
        break;
    }
    default:
        break;
    }
    f.close();
}

bool endmark(student_dat s)
{
    return strcmp(s.phone_number, "nophone") == 0;
}