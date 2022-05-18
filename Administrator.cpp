#include "Administrator.h"
#include "base64.h"
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

Administrator::Administrator()
{
    strcpy_s(password, "admin");
    strcpy_s(phone_number, "admin");
    strcpy_s(ukey, "admin");
}

void Administrator::search(int choice)
{
    vector<teacher> vt;
    teacher r, tr;
    fstream f("stu.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    do
    {
        f.read((char *)&r, sizeof(teacher));
        tr.cpy_info(r);
        vt.push_back(tr);
    } while (!endmark(r));
    f.close();
    vt.pop_back();
    //"查找模式：1.按姓名查找 2.按  xx 查找0.退出"<<endl;
    switch (choice)
    {
    case 1:
        sort(vt.begin(), vt.end(), [](teacher &a, teacher &b)
             { return a.get_name() < b.get_name(); });
        break;
    case 2: //按省份排序
        break;
    default:
        return;
    }
    for (auto i : vt)
        cout << i.get_name() << " " << i.get_phone() <<" "<<base64_decode(i.get_ukey().c_str())<< endl;
}

bool Administrator::login()
{
    string pass;
    cin >> pass;
    return pass == password;
}

void Administrator::stu_init()
{
    cout << "初始化ing" << endl;
    fstream f("stu.dat", ios::out | ios::binary);
    f.seekp(0, ios::beg);
    f.write((char *)&smark, sizeof(student));
    cout << "初始化完成" << endl;
    f.close();
}

void Administrator::tea_init()
{
    cout << "初始化ing" << endl;
    fstream f("tea.dat", ios::out | ios::binary);
    f.seekp(0, ios::beg);
    f.write((char *)&tmark, sizeof(teacher));
    cout << "初始化完成" << endl;
    f.close();
}