#include "menu.h"
#include "admin.h"
#include "student.h"
using namespace std;
void menu_start()
{
    int choice;
    cout << "欢迎使用管理系统！\n"
         << "1.学生注册\t2.管理注册\t3.学生登录\t4.退出\t9.学生初始化\t0.管理初始化" << endl;
    cin >> choice;
    switch (choice)
    {
        {
        case 1:
        {
            student stu;
            stu.signup();
            cout << "返回菜单ing" << endl;
            break;
        }
        case 3:
        {
            student stu;
            if(stu.login())
            {
                stu.set_parents_info();
            }
            cout << "返回菜单ing" << endl;
            sleep();
            cls();
            break;
        }
        case 4:
            cout << "退出ing" << endl;
            exit(0);
        case 9:
            cout << "初始化ing" << endl;
            stu_init();
        default:
            break;
        }
    }
}

const student_dat mark = {"nophone", "\0", "\0", "\0", "\0", "\0", "\0", "\0"};
void stu_init()
{
    fstream outfile("stu.dat", ios::out | ios::binary);
    outfile.seekp(0, ios::beg);
    outfile.write((char *)&mark, sizeof(student_dat));
    cout << "初始化完成" << endl;
    outfile.close();
}
