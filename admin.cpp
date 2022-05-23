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
    cout << "\n" << vt.size() << " teacher(s)" << endl;
}

bool admin::login()
{
    cls();
    string pass;
    cin >> pass;
    return pass == password;
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