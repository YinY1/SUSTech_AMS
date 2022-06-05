#include "manager.h"
#include "base64.h"
#include "student.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void manager::set_ukey()
{
    char key[20];
    cout << "\n[INFO]please input ukey：\n"
         << endl;
    cin >> key;
    strcpy_s(ukey, key);
}

bool manager::ukey_check()
{
    cout << "\n[INFO]请输入操作密码：\n"
         << endl;
    string key;
    cin >> key;
    return base64_encode(key) == ukey;
}

vector<student> manager::_sort(int choice) //排序
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
        cout << "\n[INFO]暂无学生数据！" << endl;
        return vs;
    }
    //"排序模式：1.按姓名 2.按成绩(仅能在这里approval) 3.按省份 0.退出"<<endl;
    switch (choice)
    {
    case 0: //按综评成绩排序
        for (auto it = vs.begin(); it != vs.end();)
        {
            if (it->get_is_admitted() != 1)//删除其中审核未通过的学生
                it = vs.erase(it);
            else
                it++;
        }
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_overall_score() > b.get_overall_score(); });
        break;
    case 1:
        // sort会调用=进行swap,所以不要随意重载=
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_name() < b.get_name(); }); // lambda表达式
        break;
    case 2:
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_final_score() > b.get_final_score(); });
        break;
    case 3: //按省份排序
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_province() < b.get_province(); });
        break;
    case 4: //按年龄排序
        sort(vs.begin(), vs.end(), [](student &a, student &b)
             { return a.get_birthday() < b.get_birthday(); });
        break;
    default:
        break;
    }
    return vs;
}