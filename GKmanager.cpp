#include "admin.h"
#include "control.h"
#include "student.h"
#include <fstream>
#include <iostream>

using namespace std;

void stu_init();

int main()
{
    while (1)
    {
        int choice;
        cls();
        cout << "欢迎使用管理系统！\n"
             << "1.学生注册\t2.管理注册\t3.学生登录\t5.找回密码(学生)\n\n6.报考指南\t8.学生初始化\t9.管理初始化\t0.退出" << endl;
        cin >> choice;
        switch (choice)
        {
            {
            case 1:
            {
                student stu;
                stu.signup();
                cout << endl;
                pause();
                cout << "\n返回菜单ing" << endl;
                sleep();
                break;
            }
            case 3:
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
                break;
            }
            case 5:
            {
                student stu;
                stu.rechieve_password();
                pause();
                break;
            }
            case 8:
            {
                cout << "初始化ing" << endl;
                stu_init();
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
void stu_init()
{
    fstream outfile("stu.dat", ios::out | ios::binary);
    outfile.seekp(0, ios::beg);
    outfile.write((char *)&mark, sizeof(student));
    cout << "初始化完成" << endl;
    outfile.close();
    pause();
}
