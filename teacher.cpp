#include "teacher.h"
#include "base64.h"
#include "check.h"
#include "control.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const teacher tmark = teacher();

void teacher::signup() //只提供给管理员使用
{
    int count = 10000;
    teacher t;
    fstream f("data\\teacher.dat", ios::in | ios::out | ios::binary);
    f.seekp(0, ios::beg);
    string phone = base64_encode(set_phone_number());
    while (f.read((char *)&t, sizeof(teacher)) && !endmark(t))
    {
        if (phone == t.get_phone_number())
        {
            cerr << "\n[WRONG]The number has been registered\n"
                 << endl;
            pause();
            return;
        }
        count++;
    }
    f.seekp(-long(sizeof(teacher)), ios::cur);
    cout << "id:" << count << endl;
    strcpy_s(t.id, base64_encode(to_string(count)).c_str());
    set_name();
    // set_college();
    set_password();
    set_ukey();
    strcpy_s(t.phone_number, phone.c_str());
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
        cout << "\n[INFO]请输入账号：\t 输入0返回\n"
             << endl;
        cin >> key;
        if (key[0] == '0')
            return 0;
        if (read(key))
        {
            cls();
            return 1;
        }
        else
            cerr << "\n[WRONG]用户不存在！请重新输入账号！\t输入0返回\n"
                 << endl;
    }
    return 0;
}

void teacher::approval()
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
    string sname;
    while (count < vs.size())
    {
        cls();
        sname = vs[count].get_name();
        //查看学生信息
        while (1)
        {
            cout << "\n[INFO]目前还剩 " << vs.size() - count << " 位学生未审核\n"
                 << "\n[INFO]请输入要对 " << sname << " 进行的的操作：\n\n"
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
                cerr << "\n[WRONG]输入错误，请重新输入\n"
                     << endl;
        }
        //计算成绩
        float test_score = 0;
        while (1)
        {
            cout << "\n[INFO]请输入 " << sname << " 的校测成绩：\n\n";
            cin >> test_score;
            if (test_score >= 0 && test_score <= 100)
            {
                cout << "\n[INFO]校测成绩为：" << test_score << endl;
                break;
            }
            else
                cerr << "\n[WRONG]输入错误，请重新输入\n"
                     << endl;
        }
        //审批
        int a_flag;
        cout << "\n[INFO]是否通过审核？\n\n1.是 2.否\n"
             << endl;
        cin >> a_flag;
        student s, ts;
        fstream f("data\\student.dat", ios::in | ios::out | ios::binary);
        f.seekp(0, ios::beg);
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_phone_number() == vs[count - 1].get_phone_number())
            {
                while (1)
                {
                    if (ukey_check())
                    {
                        s.set_is_admitted(a_flag); // 0为未审批，1为通过，2为未通过
                        if (a_flag == 1)
                            s.set_overall_score(test_score); //设置总成绩
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
    cout << "\n[SUCCESS]审批完毕！\n"
         << endl;
    cin.sync();
}

bool teacher::read(char key[])
{
    string ekey = base64_encode(key);
    teacher t;
    fstream f("data\\teacher.dat", ios::in | ios::binary);
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
    cout << "\n[INFO]请输入密码：\n"
         << endl;
    while (cin >> pass)
    {
        if (strcmp(base64_encode(pass).c_str(), t.password) == 0)
        {
            this->cpy_info(t); //读取信息
            break;
        }
        cerr << "\n[WRONG]密码错误，请重新输入：\n"
             << endl;
    }
    f.close();
    return 1;
}

void teacher::display(int choice) //特定需求查找
{
    student s, ts;
    fstream f("data\\student.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    switch (choice)
    {
    case 1: //按姓名查找
    case 2: //按学籍号查找
    {
        const char *p[] = {"姓名", "学籍号"};
        string str, n;
        cout << "请输入" << p[choice - 1] << endl;
        cin >> str;
        bool flag = 0;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (choice == 1)
                n = ts.get_name();
            else
                n = ts.get_student_number();
            if (n == str)
            {
                cout << "\n"
                     << ts.get_name() << "\n学籍号:" << ts.get_student_number() << "\t\t总分 " << ts.get_final_score() << "\t";
                ts.print_is_admitted();
                flag = 1;
                break;
            }
        }
        if (!flag)
            cerr << "\n[WRONG]没有找到该学生\n"
                 << endl;
        break;
    }
    case 3: //按学校代码查找
    {
        vector<student> vs;
        string str;
        cout << "\n[INFO]请输入学校代码(名称)：\n"
             << endl;
        cin >> str;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (str == ts.get_school_name())
                vs.push_back(ts);
        }
        if (vs.empty())
            cerr << "\n[WRONG]没有找到该学校的学生\n"
                 << endl;
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_final_score() > b.get_final_score(); });
        cls();
        cout << "\n[INFO]该学校的报名学生如下\n"
             << endl;
        for (auto i : vs)
        {
            cout << "\n"
                 << i.get_name() << "\t\t总分 " << i.get_final_score() << "\t";
            i.print_is_admitted();
        }
        break;
    }
    case 4: //按指定年龄范围
    {
        cls();
        string beg, end;
        while (1)
        {
            cout << "\n[INFO]请输入起始出生日期：(如：20220601)\n"
                 << endl;
            cin >> beg;
            if (beg == "0")
                return;
            if (date_check(beg))
                break;
        }
        while (1)
        {
            cout << "\n[INFO]请输入结束出生日期：(如：20220602)\n"
                 << endl;
            cin >> end;
            if (end == "0")
                return;
            if (end < beg)
            {
                cout << "\n[INFO]结束日期不能小于起始日期，请重新输入：\n"
                     << endl;
                continue;
            }
            if (date_check(end))
                break;
        }
        cls();
        vector<student> vs;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_birthday() >= beg && ts.get_birthday() <= end)
                vs.push_back(ts);
        }
        cout << "\n[INFO]年龄范围排序如下：\n"
             << endl;
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_birthday() < b.get_birthday(); });
        for (auto i : vs)
        {
            cout << "\n"
                 << i.get_name() << "\n  总分 " << i.get_final_score()
                 << "\n  出生日期 " << i.get_birthday() << endl;
            i.print_is_admitted();
        }
        cout << "\n[INFO]共有 " << vs.size() << " 个学生" << endl;
        break;
    }
    case 5: //按分数段查找
    {
        int score;
        cout << "请输入最低分为多少分？：" << endl;
        cin >> score;
        vector<student> vs;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_final_score() >= score)
                vs.push_back(ts);
        }
        if (vs.size() == 0)
            cout << "\n\n没有找到 " << score << " 分以上的学生" << endl;
        else
        {
            sort(vs.begin(), vs.end(), [](student &a, student &b)
                 { return a.get_final_score() > b.get_final_score(); });
            cls();
            for (auto i : vs)
            {
                cout << "\n"
                     << i.get_name() << "\t\t总分 " << i.get_final_score() << endl;
                i.print_is_admitted();
            }
        }
        break;
    }
    case 6: //未审核
    case 7: //已过审的学生
    case 8: //未过审的学生
    {
        const char *p[] = {"未审核", "已过审", "未过审"};
        vector<student> vs;
        while (f.read((char *)&s, sizeof(student)) && !endmark(s))
        {
            ts.cpy_info(s);
            if (ts.get_is_admitted() == (choice - 6))
                vs.push_back(ts);
        }
        if (vs.empty())
            cout << "\n\n没有" << p[choice - 6] << "的学生" << endl;
        else
        {
            sort(vs.begin(), vs.end(), [](student &a, student &b)
                 { return a.get_final_score() > b.get_final_score(); }); //按分数高低排序
            cls();
            cout << "\n\n"
                 << p[choice - 6] << "的学生如下：\n"
                 << endl;
            for (auto i : vs)
            {
                cout << "\n"
                     << i.get_name() << "\t\t总分 " << i.get_final_score() << endl;
                i.print_is_admitted();
            }
        }
        break;
    }
    }
    f.close();
}

void teacher::cpy_info(const teacher &t) //登录后读取教师信息
{
    strcpy_s(password, t.password);
    strcpy_s(id, base64_decode(t.id).c_str());
    strcpy_s(phone_number, base64_decode(t.phone_number).c_str());
    strcpy_s(name, base64_decode(t.name).c_str());
    strcpy_s(ukey, t.ukey);
}