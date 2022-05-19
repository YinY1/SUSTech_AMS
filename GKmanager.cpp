#include "admin.h"
#include "control.h"
#include "student.h"
#include "teacher.h"
#include "check.h"
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
    while (1)
    {
        string choice;
        cls();
        cout << "欢迎使用管理系统！\n"
             << "1.学生注册\t2.管理登录\t3.学生登录\t4.教师登录\n\n5.找回密码(学生)\t6.报考指南\t7.学生初始化\t8.教师初始化\t0.退出" << endl;
        cin.ignore();
        getline(cin, choice);
        if (choice_check(choice, 0, 8))
        {
            pause();
            continue;
        }
        switch (stoi(choice))
        {
            {
            case 1:
            {
                stu_signup();
                break;
            }
            case 2:
            {
                admin_login();
                pause();
                break;
            }
            case 3:
            {
                stu_login();
                break;
            }
            case 4:
            {
                tea_login();
                break;
            }
            case 5:
            {
                stu_rechieve_password();
                break;
            }
            case 7:
            {
                admin a;
                a.stu_init();
                pause();
                cls();
                break;
            }
            case 8:
            {
                admin a;
                a.tea_init();
                pause();
                cls();
                break;
            }
            case 0:
            {
                cls();
                cout << "欢迎再次使用:D" << endl;
                sleep();
                exit(0);
            }
            default:
            {
                break;
            }
            }
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
            cout << "请选择你要进行的操作：\n1.查看\\修改个人基本信息\t2.查看\\修改家庭成员信息\t3.填写个人经历\t4.填写成绩\n5.设置密保问题\t6.修改密码\t7.删除账户\t0.退出登录" << endl;
            string choice;
            getline(cin, choice);
            if (choice_check(choice, 0, 7))
            {
                pause();
                continue;
            }
            switch (stoi(choice))
            {
            case 1:
            {
                stu.show(1);
                stu.set_basic_info();
                break;
            }
            case 2:
            {
                stu.show(2);
                stu.set_parents_info();
                break;
            }
            case 3:
            {
                stu.show(3);
                stu.set_experience();
                break;
            }
            case 4:
            {
                stu.show(4);
                stu.set_score();
                break;
            }
            case 5:
            {
                stu.set_security_question();
                break;
            }
            case 6:
            {
                if (stu.change_password())
                    flag = 0;
                break;
            }
            case 7:
            {
                if (stu.cancel_account())
                    flag = 0;
                break;
            }
            case 0:
            {
                flag = 0;
                break;
            }
            default:
                break;
            }
        }
        cls();
        cout << "已成功登出！" << endl;
    }
    cout << "\n返回菜单ing" << endl;
    sleep();
    cls();
}

void stu_signup()
{
    student stu;
    stu.signup();
    cout << endl;
    pause();
    cout << "\n返回菜单ing" << endl;
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
        cout << "\n登录成功。" << endl;
        while (1)
        {
            cout << "\n操作:\n1.按姓名查找 2.按学籍号查找 3.按分数段查找\n\n"
                 << "4.列出已录取的学生 5.列出未录取的学生\n\n"
                 << "6.按姓名排序 7.按成绩排序 8.按省份排序\n\n"
                 << "9.进行录取审核 0.退出\n"
                 << endl;
            string choice;
            getline(cin, choice);
            if (choice_check(choice, 0, 9))
            {
                pause();
                continue;
            }
            switch (stoi(choice))
            {
            case 1:
            {
                t.show(1);
                pause();
                break;
            }
            case 2:
            {
                t.show(2);
                pause();
                break;
            }
            case 3:
            {
                t.show(3);
                pause();
                break;
            }
            case 4:
            {
                t.show(4);
                pause();
                break;
            }
            case 5:
            {
                t.show(5);
                pause();
                break;
            }
            //可以简单整合一下
            case 6:
            {
                vector<student> vs = t._sort(1);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                pause();
                break;
            }
            case 7:
            {
                vector<student> vs = t._sort(2);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                pause();
                break;
            }
            case 8:
            {
                vector<student> vs = t._sort(3);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                pause();
                break;
            }
            case 9:
            {
                t.admit();
                pause();
                break;
            }
            case 0:
            {
                cls();
                cout << "\n已成功登出！\n"
                     << endl;
                pause();
                return;
            }
            default:
                cls();
                return;
            }
            cls();
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
            cout << "choice: 1.showt,2.inits,3.initt,4.sett,0.exit" << endl;
            string choice;
            getline(cin, choice);
            if (choice_check(choice, 0, 4))
            {
                pause();
                continue;
            }
            switch (stoi(choice))
            {
            case 1:
            {
                a.show(1);
                pause();
                break;
            }
            case 2:
            {
                cout << "ukey?" << endl;
                if (a.ukey_check())
                {
                    a.stu_init();
                }
                else
                    cout << "ukey error" << endl;
                pause();
                break;
            }
            case 3:
            {
                cout << "ukey?" << endl;
                if (a.ukey_check())
                {
                    a.tea_init();
                }
                else
                    cout << "ukey error" << endl;
                pause();
                break;
            }
            case 4:
            {
                cout << "ukey?" << endl;
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
                cout << "\nWhat's wrong with u?" << endl;
                pause();
                break;
            }
        }
    }
    else
    {
        cout << "WRONG" << endl;
    }
}
//