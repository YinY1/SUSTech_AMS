#include "admin.h"
#include "base64.h"
#include "control.h"
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const student smark = student();
const teacher tmark = teacher();

admin::admin()
{
    strcpy_s(password, "admin");
    strcpy_s(phone_number, "12345678901");
    strcpy_s(ukey, "YWRtaW4=");
}

void admin::display(int choice)
{
    vector<teacher> vt;
    teacher r, tr;
    fstream f("tea.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    while (f.read((char *)&r, sizeof(teacher)) && !endmark(r))
    {
        tr.cpy_info(r);
        vt.push_back(tr);
    }
    f.close();
    if (vt.empty())
    {
        cls();
        cout << "\nThere is NO such TEACHER in your college:D" << endl;
        return;
    }
    //"查找模式：1.按姓名查找 2.按ID 查找0.退出"<<endl;
    switch (choice)
    {
    case 1:
        sort(vt.begin(), vt.end(), [](teacher &a, teacher &b)
             { return a.get_name() < b.get_name(); });
        break;
    case 2:
        sort(vt.begin(), vt.end(), [](teacher &a, teacher &b)
             { return a.get_id() < b.get_id(); });
        break;
    default:
        return;
    }
    for (auto i : vt)
        cout << "NO." << i.get_id() << " " << i.get_name() << " " << i.get_phone() << " " << base64_decode(i.get_ukey().c_str()) << endl;
    cout << "\n"
         << vt.size() << " teacher(s)" << endl;
}

bool admin::login()
{
    cls();
    string pass;
    cin >> pass;
    return pass == password;
}

void admin::admit()
{
    size_t num;
    string s;
    vector<student> vs = _sort(0);
    while (1)
    {
        cls();
        cout << "\n[INFO]total:" << vs.size() << "\n[INFO]Please enter the number of students to be admitted\n"
             << endl;
        cin >> num;
        if (num == 0)
            return;
        if (num < 0 || num > vs.size())
        {
            cout << "\n[INFO]Invalid input!\n"
                 << endl;
            pause();
            cin.sync();
            continue;
        }
        else
        {
            cout << "\n[INFO]The following students will be admitted:\n"
                 << endl;
            for (size_t i = 0; i < num; i++)
                cout << vs[i].get_name() << "\t\t" << vs[i].get_overall_score() << endl;
            cout << "\n[INFO]total:" << num << "\n[INFO]Are you sure to admit them?(y/n)" << endl;
            cin >> s;
            if (s == "y")
            {
                if (ukey_check())
                {
                    fstream f("admit.txt", ios::out);
                    f.seekp(0, ios::beg);
                    for (size_t i = 0; i < num; i++)
                        f << vs[i].get_name() <<"\t\t"<< vs[i].get_id() << endl;
                    f.close();
                    cout << "\n[INFO]Admission success!\n"
                         << endl;
                    pause();
                    return;
                }
                else
                {
                    cout << "\n[WRONG]ukey error" << endl;
                    pause();
                    continue;
                }
            }
            else
            {
                cout << "\n[INFO]Canceled!" << endl;
                pause();
                break;
            }
        }
    }
}

void admin::stu_init()
{
    fstream f("stu.dat", ios::out | ios::binary);
    f.seekp(0, ios::beg);
    f.write((char *)&smark, sizeof(student));
    cout << "\nInitialization \"stu.dat\" complete" << endl;
    f.close();
}

void admin::tea_init()
{
    fstream f("tea.dat", ios::out | ios::binary);
    f.seekp(0, ios::beg);
    f.write((char *)&tmark, sizeof(teacher));
    cout << "\nInitialization \"tea.dat\" complete" << endl;
    f.close();
}