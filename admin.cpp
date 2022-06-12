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
#include <iomanip>
using namespace std;

const student smark = student();
const teacher tmark = teacher();

admin::admin()
{
    strcpy_s(password, "admin");
    strcpy_s(phone_number, "12345678901");
    strcpy_s(ukey, "YWRtaW4="); // admin base64加密后
}

void admin::display(int choice)
{
    vector<teacher> vt;
    teacher r, tr;
    fstream f("data\\teacher.dat", ios::in | ios::binary);
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
        cout << "\nThere is NO TEACHERs in your college:D" << endl;
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
        cout << "NO." << i.get_id() << " " << i.get_name() << " " << i.get_phone_number() << " " << base64_decode(i.get_password().c_str()) << " " << base64_decode(i.get_ukey().c_str()) << endl;
    cout << "\n"
         << vt.size() << " teacher(s)" << endl;
}

bool admin::login()
{
    cls();
	cout<<"\n[INFO]please input your password:"<<endl;
    string pass;
    cin >> pass;
    return pass == password;
}

void admin::admit()
{
	//检查审批、录取的状态
	fstream infile("data\\admission_list.txt", ios::in);
	string s;
	infile >> s;
	if(s=="")
	{
		cout<<"\nRegistration is not yet closed"<<endl;
		pause();
		infile.close();
		return;
	}
	else if(s!="ddl")
	{
		cout<<"\nThe admission list has been published"<<endl;
		pause();
		infile.close();
		return;
	}
	infile.close();
	//进行录取
    size_t num;
    vector<student> vs = _sort(0);
    for (auto it = vs.begin(); it != vs.end();)
    {
        if (it->get_overall_score() == 0)
            it = vs.erase(it);
        else
            it++;
    }
    if (vs.empty())
    {
        cls();
        cout << "\nThere is NO STUDENTs in your college:D" << endl;
        pause();
        return;
    }
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
                    fstream f("data\\admission_list.txt", ios::out);
                    f.seekp(0, ios::beg);
                    f<<setiosflags(ios::left)<<setw(30)<<"姓名"<<setw(20)<<"身份证\t"<<"成绩"<<endl;
                    for (size_t i = 0; i < num; i++)
                        f << setiosflags(ios::left)<<setw(30)
                        <<vs[i].get_name() <<setw(20)  << vs[i].get_id() <<"\t" <<vs[i].get_overall_score()<<endl;
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

void admin::deadline()
{
	fstream f("data\\admission_list.txt", ios::in|ios::out);
	if(f.get()==EOF)
	{
		f<<"ddl"<<endl;
		cout<<"success"<<endl;
	}
	else
		cerr << "wrong" << endl;
	f.close();
}

void admin::stu_init()
{
    fstream f("data\\student.dat", ios::out | ios::binary);
    f.seekp(0, ios::beg);
    f.write((char *)&smark, sizeof(student));
    f.close();
	f.open("data\\admission_list.txt", ios::out);
	f.close();
}

void admin::tea_init()
{
    fstream f("data\\teacher.dat", ios::out | ios::binary);
    f.seekp(0, ios::beg);
    f.write((char *)&tmark, sizeof(teacher));
    f.close();
}