#include "student.h"
#include "base64.h"
#include "check.h"

//后包含windows.h会导致byte重定义,命名空间std会被重复包含https://github.com/msys2/MINGW-packages/issues/7035
//所以不要在头文件using,实在不想打std::可以在cpp里面using，尽量不要using namespace，除非确定没有重复。
using namespace std;

const student mark = student();

void student::signup()
{
    strcpy_s(phone_number, set_phone_number().c_str());
    //查重
    if (read(phone_number, 0))
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
    strcpy_s(this->province, province.c_str());
}

void student::set_student_number()
{
    cout << "\n请输入学籍号：" << endl;
    cin >> student_number;
    cout << "请再次输入学籍号！" << endl;
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
    strcpy_s(this->nation, nation.c_str());
}

void student::set_school_name()
{
    string school_name;
    cout << "\n请输入学校名称：" << endl;
    while (cin >> school_name)
    {
        if (school_name.length() < 45)
        {
            strcpy_s(this->school_name, school_name.c_str());
            break;
        }
        else
        {
            cout << "学校名称过长！请重新输入！" << endl;
        }
    }
    strcpy_s(this->school_name, school_name.c_str());
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
            strcpy_s(political_status, p[num - 1]);
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
            show(1);
            pause();
            break;
        case 0:
            cls();
            write(1);
            return;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        cout << "\n请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.学籍号\n6.身份证\n7.显示目前信息\n0.退出\n"
             << endl;
    }
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
            strcpy_s(dad_phone_number, set_phone_number().c_str());
            break;
        case 4:
            strcpy_s(mom_phone_number, set_phone_number().c_str());
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
            show(2);
            pause();
            break;
        case 0:
            write(2);
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

//有空用vector改改
void student::set_experience()
{
    int choice;
    cout << "\n请选择需要进行的操作：\n"
         << "1.填写经历\t2.查看经历\t"
         << "0.返回" << endl;
    while (cin >> choice)
    {
        switch (choice)
        {
        case 1:
        {
            string experience;
            cout << "\n请输入你的中学经历：（当最后一个字为#时结束输入）\n"
                 << "格式如下：\n学校名称\t阶段\t入学时间-毕业/转校时间\t，担任职务/获得奖项\n"
                 << "XXXX中学，初中/，20XX-20XX，班长，三好学生，学习之星\n"
                 << "XXXX学校,高中，20XX-20XX，班长，三好学生，学习之星\n"
                 << "请不要超过500字！！！" << endl;
            cin.ignore();
            getline(cin, experience, '#');
            strcpy_s(this->experience, experience.c_str());
            break;
        }
        case 2:
            show(3);
            pause();
            break;
        case 0:
            cls();
            cout << "输入完成！正在返回……" << endl;
            write(3);
            return;
        default:
            cout << "输入错误，请重新输入：" << endl;
            break;
        }
        cout << "\n请选择需要进行的操作：\n"
             << "1.填写经历\t2.查看经历\t"
             << "0.返回" << endl;
    }
}

void student::set_score()
{
    int select;
    char *test[] = {"高一上期末考", "高一下期末考", "高二上期末考", "高二下期末考", "高三模拟考一（校级以上）", "高三模拟考二（校级以上）", "高三模拟考三（校级以上）", "学业水平考试", "高考"};
    cout << "\n请选择需要进行的操作：\n"
         << "1.填写成绩\t2.查看成绩\t"
         << "0.返回" << endl;
    while (cin >> select)
    {
        switch (select)
        {
        case 1:
        {
            int choice;
            memset(score, 0, sizeof(score));
            cout << "\n请选择需要填写的成绩：\n"
                 << "1.高一上期末考\t2.高一下期末考\t3.高二上期末考\t4.高二下期末考\n"
                 << "5.高三模拟考一（校级以上）\t6.高三模拟考二（校级以上）\t7.高三模拟考三（校级以上）\t8.学业水平考试\t9.高考\n0.返回" << endl;
            while (cin >> choice)
            {
                if (choice == 0)
                {
                    cls();
                    break;
                }
                if (choice > 9)
                {
                    cout << "\n输入错误！请重新输入！" << endl;
                    continue;
                }
                cout << "请按照顺序输入你的成绩，没有的请填0（150分制）：语文  数学  外语  物理  化学  生物  地理  政治  历史  技术  年级排名  年级总人数\n\n"
                     << "请输入 " << test[choice - 1] << " 成绩：" << endl;
                for (int i = 0; i < 12; i++)
                {
                    cin >> score[choice - 1][i];
                    if (i < 10)
                        score[choice - 1][12] += score[choice - 1][i]; //总分
                }
                cout << "\n请选择需要填写的成绩：\n"
                     << "1.高一上期末考\t2.高一下期末考\t3.高二上期末考\t4.高二下期末考\n"
                     << "5.高三模拟考一（校级以上）\t6.高三模拟考二（校级以上）\t7.高三模拟考三（校级以上）\t8.学业水平考试\t9.高考\n0.返回" << endl;
            }
            break;
        }
        case 2:
            show(4);
            pause();
            break;
        case 0:
            cls();
            cout << "输入完成！正在返回……" << endl;
            write(4);
            return;
        default:
            cout << "输入错误，请重新输入：" << endl;
        }
    }
}

void student::show(int choice)
{
    switch (choice)
    {
    case 1:
        cout << "\n姓名：" << name
             << "\n性别：" << gender
             << "\n学籍号：" << student_number
             << "\n身份证号码：" << id
             << "\n高考省份（地区）：" << province
             << "\n手机号码：" << base64_decode(phone_number)
             << "\n民族：" << nation
             << "\n政治面貌：" << political_status
             << "\n学校名称：" << school_name << "\n"
             << endl;
        break;
    case 2:
        cout << "\n父亲姓名:" << dad_name
             << "\n父亲电话:" << dad_phone_number
             << "\n父亲职业:" << dad_job
             << "\n父亲工作地址:" << dad_work_address
             << "\n母亲姓名:" << mom_name
             << "\n母亲电话:" << mom_phone_number
             << "\n母亲职业:" << mom_job
             << "\n母亲工作地址:" << mom_work_address
             << endl;
    case 3:
    case 4:
        break;
    }
}

bool student::read(char key[], int choice)
{
    student r;
    char ekey[20];
    strcpy_s(ekey, base64_encode(key).c_str());
    fstream f("stu.dat", ios::in | ios::out | ios::binary);
    f.seekg(0, ios::beg);
    do
    {
        f.read((char *)&r, sizeof(student));
    } while (strcmp(ekey, r.phone_number) && !endmark(r));
    if (strcmp(ekey, r.phone_number))
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
                strcpy_s(id, base64_decode(r.id).c_str());
                strcpy_s(gender, base64_decode(r.gender).c_str());
                strcpy_s(student_number, base64_decode(r.student_number).c_str());
                strcpy_s(name, base64_decode(r.name).c_str());
                strcpy_s(province, base64_decode(r.province).c_str());
                strcpy_s(phone_number, ekey);
                strcpy_s(nation, base64_decode(r.nation).c_str());
                strcpy_s(political_status, base64_decode(r.political_status).c_str());
                strcpy_s(school_name, base64_decode(r.school_name).c_str());
                strcpy_s(dad_name, base64_decode(r.dad_name).c_str());
                strcpy_s(dad_phone_number, base64_decode(r.dad_phone_number).c_str());
                strcpy_s(dad_job, base64_decode(r.dad_job).c_str());
                strcpy_s(dad_work_address, base64_decode(r.dad_work_address).c_str());
                strcpy_s(mom_name, base64_decode(r.mom_name).c_str());
                strcpy_s(mom_phone_number, base64_decode(r.mom_phone_number).c_str());
                strcpy_s(mom_job, base64_decode(r.mom_job).c_str());
                strcpy_s(mom_work_address, base64_decode(r.mom_work_address).c_str());
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
    student w;
    fstream f("stu.dat", ios::in | ios::out | ios::binary);
    f.seekp(0, ios::beg);
    do
    {
        f.read((char *)&w, sizeof(student));
    } while (strcmp(phone_number, w.phone_number) && !endmark(w));
    switch (choice)
    {
    case 0: //注册
    {
        f.seekp(-long(sizeof(student)), ios::cur);
        set_name();
        set_password();
        //用base64简单加密了一下
        strcpy_s(w.password, base64_encode(password).c_str());
        strcpy_s(w.phone_number, base64_encode(phone_number).c_str());
        strcpy_s(w.name, base64_encode(name).c_str());
        f.write((char *)&w, sizeof(student));
        f.write((char *)&mark, sizeof(student));
        cout << "注册成功" << endl;
        break;
    }
    case 1: //写个人基本信息
    {
        strcpy_s(w.province, base64_encode(province).c_str());
        strcpy_s(w.nation, base64_encode(nation).c_str());
        strcpy_s(w.political_status, base64_encode(political_status).c_str());
        strcpy_s(w.school_name, base64_encode(school_name).c_str());
        strcpy_s(w.student_number, base64_encode(student_number).c_str());
        strcpy_s(w.id, base64_encode(id).c_str());
        strcpy_s(w.gender, base64_encode(gender).c_str());
        //置写指针位置，设置错误会覆盖信息
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    }
    case 2: //写家长信息
    {
        strcpy_s(w.dad_name, base64_encode(dad_name).c_str());
        strcpy_s(w.dad_phone_number, base64_encode(dad_phone_number).c_str());
        strcpy_s(w.mom_name, base64_encode(mom_name).c_str());
        strcpy_s(w.mom_phone_number, base64_encode(mom_phone_number).c_str());
        strcpy_s(w.dad_work_address, base64_encode(dad_work_address).c_str());
        strcpy_s(w.mom_work_address, base64_encode(mom_work_address).c_str());
        strcpy_s(w.dad_job, base64_encode(dad_job).c_str());
        strcpy_s(w.mom_job, base64_encode(mom_job).c_str());
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    }
    case 3: //写个人经历
    {
        strcpy_s(w.experience, base64_encode(experience).c_str());
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    }
    case 4: //写成绩
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 13; j++)
                w.score[i][j] = score[i][j];
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    }
    default:
        cout << "white（写错了）" << endl;
        pause();
        break;
    }
    f.close();
}

bool endmark(student s)
{
    return strcmp((s.get_phone()).c_str(), "nophone") == 0;
}