#include "teacher.h"
#include "base64.h"
#include "control.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

const teacher tmark = teacher();

void teacher::signup() //只提供给管理员使用
{
    int count = 10000;
    teacher t;
    fstream f("tea.dat", ios::in | ios::out | ios::binary);
    f.seekp(0, ios::beg);
    while (f.read((char *)&t, sizeof(teacher)) && !endmark(t))
    {
        count++;
    }
    f.seekp(-long(sizeof(teacher)), ios::cur);
    cout << "id:" << count << endl;
    strcpy(t.id, base64_encode(to_string(count)).c_str());
    set_name();
    // set_college();
    set_password();
    set_ukey();
    strcpy_s(t.phone_number, base64_encode(set_phone_number()).c_str());
    // cpinfo
    strcpy_s(t.password, base64_encode(password).c_str());
    strcpy_s(t.name, base64_encode(name).c_str());
    strcpy_s(t.ukey, base64_encode(ukey).c_str());
    f.write((char *)&t, sizeof(teacher));
    f.write((char *)&tmark, sizeof(teacher));
    cout << "\nsuccessfully signed up\n"
         << endl;
    f.close();
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
            return 1;
        }
        else
            cout << "用户不存在！请重新输入账号！\t输入0返回" << endl;
    }
    return 0;
}

void teacher::admit()
{
    vector<student> vs = _sort(2);
    //从容器中删除已被审核的学生
    for (auto it = vs.begin(); it != vs.end();)
    {
        if (it->get_is_admitted())
            it = vs.erase(it);
        else
            it++;
    }
    size_t count = 0;
    int sel;
    while (count < vs.size())
    {
        cls();
        while (1)
        {
            cout << "\n目前还剩 " << vs.size() - count << " 位学生未审核\n"
                 << "\n请输入要对 " << vs[count].get_name() << " 进行的的操作：\n\n"
                 << "1.查看个人信息 \t2.查看家庭情况 \t3.查看个人经历 \t4.查看考试情况\n9.下一步 \t0.退出录取操作" << endl;
            cin >> sel;
            if (sel >= 1 && sel <= 4)
                vs[count].display(sel);
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
        cout << "是否通过审核？1.是 2.否" << endl;
        cin >> a_flag;
        student s, ts;
        fstream f("stu.dat", ios::in | ios::out | ios::binary);
        f.seekp(0, ios::beg);
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_phone() == vs[count - 1].get_phone())
            {
                while (1)
                {
                    if (ukey_check())
                    {
                        s.set_is_admitted(a_flag); // 0为未审批，1为通过，2为未通过
                        f.seekp(-long(sizeof(student)), ios::cur);
                        f.write((char *)&s, sizeof(student));
                        pause();
                        break;
                    }
                    else
                        cout << "wrong" << endl;
                }
                break;
            }
        }
        f.close();
    }
    cls();
    cout << "\n录取完毕！" << endl;
    cin.ignore();
}

bool teacher::read(char key[])
{
    string ekey = base64_encode(key);
    teacher t;
    fstream f("tea.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    do
    {
        f.read((char *)&t, sizeof(teacher));
    } while (!endmark(t) && ekey != t.phone_number && ekey != t.id); //通过手机号码或ID登录
    if (ekey != t.phone_number && ekey != t.id)
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
            this->cpy_info(t); //读取信息
            break;
        }
        cout << "\n密码错误，请重新输入：" << endl;
    }
    f.close();
    return 1;
}

void teacher::display(int choice) //特定需求查找
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
                cout << "\n"
                     << n << "\t\t总分 " << ts.get_score() << "\t";
                ts.print_admitted();
                flag = 1;
                break;
            }
        }
        if (!flag)
            cout << "\n没有找到该学生\n"
                 << endl;
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
                cout << "\n"
                     << n << "\t\t总分 " << ts.get_score() << "\t";
                ts.print_admitted();
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
                i.print_admitted();
            }
        }
        break;
    }
    case 4:
    case 5: // 列出已（未）录取的学生
    {
        const char *p[] = {"已录取", "未录取"};
        vector<student> vs;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_is_admitted() == (choice - 3))
                vs.push_back(ts);
        }
        if (vs.empty())
            cout << "\n\n没有" << p[choice - 4] << "的学生" << endl;
        else
        {
            sort(vs.begin(), vs.end(), [](student &a, student &b)
                 { return a.get_score() > b.get_score(); }); //按分数高低排序
            cls();
            cout << "\n\n"
                 << p[choice - 4] << "的学生如下：\n"
                 << endl;
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
    while (f.read((char *)&s, sizeof(student)) && !endmark(s))
    {
        ts.cpy_info(s);
        vs.push_back(ts);
    }
    f.close();
    if (vs.empty())
    {
        cout << "\n暂无学生数据！" << endl;
        return vs;
    }
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
    strcpy_s(phone_number, base64_decode(t.phone_number).c_str());
    strcpy_s(name, base64_decode(t.name).c_str());
    strcpy_s(ukey, t.ukey);
}