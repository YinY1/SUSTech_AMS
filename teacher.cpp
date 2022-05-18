#include "teacher.h"
#include "base64.h"
#include "control.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

const teacher tmark = teacher();

void teacher::signup() //没调好,写了nophone进去
{
    teacher t;
    fstream f("tea.dat", ios::in | ios::out | ios::binary);
    f.seekp(0, ios::beg);
    do
    {
        f.read((char *)&t, sizeof(teacher));
    } while (!endmark(t));//这里之后要改
    f.seekp(-long(sizeof(teacher)), ios::cur);
    set_name();
    //set_province();
    //set_college();
    set_password();
    set_ukey();
    cout << "id:" << endl;
    string id;
    cin >> id;
    strcpy(this->id, id.c_str());
    strcpy_s(t.phone_number, base64_encode(set_phone_number()).c_str());
    // cpinfo
    strcpy_s(t.password, base64_encode(password).c_str());
    strcpy_s(t.name, base64_encode(name).c_str());
    strcpy_s(t.ukey, base64_encode(ukey).c_str());
    f.write((char *)&t, sizeof(teacher));
    f.write((char *)&tmark, sizeof(teacher));
    cout << "successfully set t?" << endl;
    f.close();
}

void teacher::admit()
{
    vector<student> vs = _sort(2);
    int count = 0, sel;
    while (1)
    {
        cls();
        while (1)
        {
            cout << "\n\n请输入要对 " << vs[count].get_name() << " 进行的的操作：\n\n"
                 << "1.查看个人信息 \t2.查看家庭情况 \t3.查看个人经历 \t4.查看考试情况\n9.下一步 \t0.退出录取操作" << endl;
            cin >> sel;
            if (sel >= 1 && sel <= 4)
                vs[count].show(sel);
            else if (sel == 9)
            {
                count++;
                break;
            }
            else if (sel == 0)
                return;
            else
                cout << "输入错误，请重新输入" << endl;
        }
        int a_flag;
        cout << "是否录取？1.是 2.否" << endl;
        cin >> a_flag;
        student s, ts;
        fstream f("stu.dat", ios::in | ios::out | ios::binary);
        f.seekp(0, ios::beg);
        while (f.read((char *)&s, sizeof(student)))
        {
            ts.cpy_info(s);
            if (ts.get_id() == vs[count - 1].get_id())
            {
                while (1)
                {
                    if (ukey_check())
                    {
                        vs[count - 1].set_is_admitted(abs(a_flag - 2));
                        break;
                    }
                    else
                        cout << "wrong" << endl;
                }
                f.seekp(-long(sizeof(student)), ios::cur);
                f.write((char *)&vs[count - 1], sizeof(student));
                break;
            }
        }
        f.close();
    }
}

bool teacher::read(char key[])
{
    char ekey[20];
    teacher t;
    fstream f("tea.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    strcpy_s(ekey, base64_encode(key).c_str());
    do
    {
        f.read((char *)&t, sizeof(teacher));
    } while (!endmark(t) && strcmp(ekey, t.phone_number));
    if (strcmp(ekey, t.phone_number))
    {
        f.close();
        return 0; //没有重复
    }
    string pass;
    cout << "\n请输入密码：" << endl;
    while (cin >> pass)
    {
        if (strcmp(base64_encode(pass).c_str(), t.password) == 0)
        {
            cout << "\n登录成功！" << endl;
            this->cpy_info(t); //读取信息
            break;
        }
        cout << "\n密码错误，请重新输入：" << endl;
    }
    f.close();
    return 1;
}

bool teacher::login()
{
    char key[15];
    while (1)
    {
        cout << "请输入账号：\t 输入0返回" << endl;
        cin >> key;
        if (key[0] == '0')
            return 0;
        if (read(key))
        {
            cls();
            cout << "欢迎" << name << endl;
            return 1;
        }
        else
            cout << "用户不存在！请重新输入账号！\t输入0返回" << endl;
    }
    return 0;
}

void teacher::search(int choice) //特定需求查找
{
    student s, ts;
    fstream f("stu.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    switch (choice)
    {
    case 1: //按姓名查找
    {
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        bool flag = 0;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            string n = ts.get_name();
            if (n == name)
            {
                cout << "\n\n"
                     << n << "\t\t总分 " << ts.get_score() << endl;
                flag = 1;
                break;
            }
        }
        if (!flag)
            cout << "\n\n没有找到该学生" << endl;
        break;
    }
    case 2: //按学籍号查找
    {
        string snum;
        cout << "请输入学籍号：" << endl;
        cin >> snum;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            string n = ts.get_student_number();
            if (n == snum)
            {
                cout << "\n\n"
                     << n << "\t\t总分 " << ts.get_score() << endl;
                break;
            }
        }
        break;
    }
    case 3: //按分数段查找
    {
        int score;
        cout << "请输入最低分为多少分？：" << endl;
        cin >> score;
        vector<student> vs;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_score() >= score)
                vs.push_back(ts);
        }
        if (vs.size() == 0)
            cout << "\n\n没有找到 " << score << " 分以上的学生" << endl;
        else
        {
            sort(vs.begin(), vs.end(), [](student &a, student &b)
                 { return a.get_score() > b.get_score(); });
            cls();
            for (auto i : vs)
            {
                cout << "\n"
                     << i.get_name() << "\t\t总分 " << i.get_score() << endl;
            }
        }
        break;
    }
    }
    f.close();
}

vector<student> teacher::_sort(int choice) //排序
{
    vector<student> vs;
    student s, ts;
    fstream f("stu.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    /* do
    {
        f.read((char *)&s, sizeof(student));
        ts.cpy_info(s);
        vs.push_back(ts);
    } while (!endmark(s));
    f.close();
    vs.pop_back(); */ //会把endmark 读进去，所以要删掉最后一个
    //试试这个
    
    while (f.read((char *)&s, sizeof(student)) && !endmark(s))
    {
        ts.cpy_info(s);
        vs.push_back(ts);
    }
    f.close();
    
    //"排序模式：1.按姓名 2.按成绩(仅能在这里admit) 3.按省份 0.退出"<<endl;
    switch (choice)
    {
    case 1:
        // sort会调用=进行swap,所以不要随意重载=
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_name() < b.get_name(); }); // lambda表达式
        break;
    case 2:
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_score() > b.get_score(); });
        break;
    case 3: //按省份排序
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_province() < b.get_province(); });
        break;
    default:
        return vs;
    }
    return vs;
}

void teacher::cpy_info(const teacher &t) //登录后读取教师信息
{
    strcpy_s(password, t.password);
    strcpy_s(id, base64_decode(t.id).c_str());
    strcpy_s(college, base64_decode(t.college).c_str());
    strcpy_s(phone_number, t.phone_number);
    strcpy_s(name, base64_decode(t.name).c_str());
    strcpy_s(province, base64_decode(t.province).c_str());
    strcpy_s(ukey, base64_decode(t.ukey).c_str());
}