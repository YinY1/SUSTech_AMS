#include "admin.h"
#include "check.h"
#include "control.h"
#include "student.h"
#include "teacher.h"
#include <fstream>
#include <iostream>
using namespace std;

void stu_signup();
void stu_login();
void stu_rechieve_password();
void tea_login();
void admin_login();

int main()
{
    string choice;
    while (1)
    {
        cls();
        middle("---------------------", 1);
        middle("欢迎使用管理系统!", 2);
        middle("---------------------", 3);
        cout << "\n[INFO]请按照提示输入选项\n\n"
             << "1.学生注册\n\n2.管理登录\n\n3.学生登录\n\n4.教师登录\n\n"
             << "5.找回密码(学生)\n\n6.报考指南\n\n0.退出\n"
             << endl;
        cin >> choice;
        int c = choice_check(choice, 0, 6);
        cls();
        switch (c)
        {
        case 1:
            stu_signup();
            break;
        case 2:
            admin_login();
            pause();
            break;
        case 3:
            stu_login();
            break;
        case 4:
            tea_login();
            break;
        case 5:
            stu_rechieve_password();
            break;
        case 6:
            cout << "no guidence" << endl;
            pause();
            break;
        case 0:
            cout << "欢迎再次使用:D" << endl;
            sleep();
            exit(0);
        default:
            cin.ignore(1024, '\n');
            continue;
        }
    }
}

void stu_login()
{
    student stu;
    if (stu.login())
    {
        bool flag = 1;
        while (flag)
        {
            cls();
            string s = " 欢迎您," + stu.get_name() + "同学!";
            middle("-----------------------", 1);
            middle(s, 2);
            middle("-----------------------", 3);
            cout << "\n[INFO]请按照提示输入选项\n\n"
                 << "1.查看\\修改个人基本信息\n\n2.查看\\修改家庭成员信息\n\n3.填写个人经历\n\n4.填写成绩\n\n5.设置密保问题\n\n6.修改密码\n\n7.删除账户\n\n0.退出登录\n " << endl;
            string choice;
            cin >> choice;
            int c = choice_check(choice, 0, 7);
            cls();
            switch (c)
            {
            case 1:
                stu.display(1);
                stu.set_basic_info();
                break;
            case 2:
                stu.display(2);
                stu.set_parents_info();
                break;
            case 3:
                stu.display(3);
                stu.set_experience();
                break;
            case 4:
                stu.display(4);
                stu.set_score();
                break;
            case 5:
                stu.set_security_question();
                break;
            case 6:
                if (stu.change_password())
                    flag = 0;
                break;
            case 7:
                if (stu.cancel_account())
                    flag = 0;
                break;
            case 0:
                flag = 0;
                break;
            default:
                cin.ignore(1024, '\n');
                continue;
            }
            cls();
            cout << "\n\n[INFO]已成功登出！\n"
                 << endl;
        }
        cout << "\n[INFO]返回菜单ing" << endl;
        sleep();
        cls();
    }
}

void stu_signup()
{
    student stu;
    stu.signup();
    cout << endl;
    pause();
    cout << "\n[INFO]返回菜单ing" << endl;
    sleep();
}

void stu_rechieve_password()
{
    student stu;
    stu.rechieve_password();
    pause();
    cls();
}

void tea_login()
{
    teacher t;
    if (t.login())
    {
        string choice;
        while (1)
        {
            cls();
            string s = " 欢迎您," + t.get_name() + "老师!";
            middle("-----------------------", 1);
            middle(s, 2);
            middle("-----------------------", 3);
            cout << "\n[INFO]请按照提示输入选项\n\n"
                 << "1.按姓名查找\n\n2.按学籍号查找\n\n3.按分数段查找\n\n"
                 << "4.列出已录取的学生\n\n5.列出未录取的学生\n\n"
                 << "6.按姓名排序\n\n7.按成绩排序\n\n8.按省份排序\n\n"
                 << "9.进行录取审核\n\n0.退出\n"
                 << endl;
            cin >> choice;
            int c = choice_check(choice, 0, 9);
            switch (c)
            {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                t.display(c);
                pause();
                break;
            case 6:
            case 7:
            case 8:
            {
                vector<student> vs = t._sort(c - 5);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                pause();
                break;
            }
            case 9:
                t.admit();
                pause();
                break;
            case 0:
                cls();
                cout << "\n[INFO]已成功登出！\n"
                     << endl;
                pause();
                return;
            default:
                pause();
                cin.ignore(1024, '\n');
                continue;
            }
        }
    }
}

void admin_login()
{
    admin a;
    if (a.login())
    {
        while (1)
        {
            cls();
            cout << "choice:\n"
                 << "1.display teacher(s) info by name\n"
                 << "2.display teacher(s) info in id order\n"
                 << "3.initialize students data\n"
                 << "4.initialize teachers data\n"
                 << "5.register teachers accounts, 0.exit" << endl;
            string choice;
            cin >> choice;
            int c = choice_check(choice, 0, 5);
            switch (c)
            {
            case 1:
            case 2:
                a.display(c);
                pause();
                break;
            case 3:
                if (a.ukey_check())
                    a.stu_init();
                else
                    cout << "ukey error" << endl;
                pause();
                break;
            case 4:
                if (a.ukey_check())
                    a.tea_init();
                else
                    cout << "ukey error" << endl;
                pause();
                break;
            case 5:
            {
                if (a.ukey_check())
                {
                    teacher t;
                    t.signup();
                    pause();
                }
                else
                    cout << "ukey error" << endl;
                break;
            }
            case 0:
                return;
            default:
                cin.ignore(1024, '\n');
                continue;
            }
        }
    }
    else
        cout << "WRONG" << endl;
}