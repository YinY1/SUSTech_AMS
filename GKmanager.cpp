#include "Administrator.h"
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
    while (1)
    {
        int choice;
        cls();
        cout << "欢迎使用管理系统！\n"
             << "1.学生注册\t2.管理登录\t3.学生登录\t4.教师登录\n\n5.找回密码(学生)\t6.报考指南\t8.学生初始化\t9.教师初始化\t0.退出" << endl;
        cin >> choice;
        switch (choice)
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
            case 8:
            {
                Administrator a;
                a.stu_init();
                pause();
                cls();
                break;
            }
            case 9:
            {
                Administrator a;
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

const student mark = student();

void stu_login()
{

    student stu;
    if (stu.login())
    {
        bool flag = 1;
        while (flag)
        {
            cout << "请选择你要进行的操作：\n1.查看\\修改个人基本信息\t2.查看\\修改家庭成员信息\t3.填写个人经历\t4.填写成绩\n5.设置密保问题\t6.修改密码\t9.删除账户\t0.退出登录" << endl;
            int select;
            cin >> select;
            switch (select)
            {
            case 0:
            {
                flag = 0;
                break;
            }
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
            case 9:
            {
                if (stu.cancel_account())
                    flag = 0;
                break;
            }
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
        cout << "登录成功。" << endl;
        while (1)
        {
            cout << "操作" << endl;
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                t.search(1);
                break;
            }
            case 2:
            {
                t.search(2);
                break;
            }
            case 3:
            {
                t.search(3);
                break;
            }
            //可以简单整合一下
            case 4:
            {
                vector<student> vs = t._sort(1);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                break;
            }
            case 5:
            {
                vector<student> vs = t._sort(2);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                break;
            }
            case 6:
            {
                vector<student> vs = t._sort(3);
                for (auto i : vs)
                    cout << "\n"
                         << i.get_name() << "\t生源： " << i.get_province() << "\t总分 " << i.get_score() << endl;
                cout << "\n共有 " << vs.size() << " 个学生" << endl;
                break;
            }
            case 7:
            {
                t.admit();
                break;
            }
            default:
                return;
            }
        }
    }
}

void admin_login()
{
    Administrator a;
    if (a.login())
    {
        while (1)
        {
            cout << "choice: 1.showt,2.inits,3.initt,4.sett,5.exit" << endl;
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                a.search(1);
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
                break;
            }
            case 4:
            {
                cout << "ukey?" << endl;
                if (a.ukey_check())
                {
                    teacher t;
                    t.signup();
                }
                else
                    cout << "ukey error" << endl;
                break;
            }
            case 5:
            {
                return;
            }
            default:
                break;
            }
        }
    }
    else
    {
        cout << "WRONG NUMBER" << endl;
    }
}
//