#include "menu.h"
#include "user.h"
#include "admin.h"
#include "student.h"
//const userdat mark = {0, "noname\0", "nopassword\0", "nonumber\0"};
const student_dat mark = {0, "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0"};
void menu_start()
{
    int choice;
    cout << "欢迎使用管理系统！\n"
         << "1.学生注册\t2.管理注册\t3.登录\t4.退出\t9.学生初始化\t0.管理初始化" << endl;
    cin >> choice;
    switch (choice)
    {
        {
        case 1:
        {
            student stu;
            stu.signup();
            cout << "返回菜单ing" << endl;
            break;}
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
    void menu_login()
    {
        userdat user;
        bool check = 0;
        cout << "请输入用户名：" << endl;
        ifstream infile("user.dat", ios::in);
        while (!check)
        {
            cin >> user.name;
            while (infile.read((char *)&user, sizeof(user)))
            {
                if (user.name != user.name)
                {
                    cout << "用户不存在！请重新输入" << endl;
                    break;
                }
                else
                {
                    check = 1;
                    break;
                }
            }
        }
        check = 0;
        cout << "请输入密码：" << endl;
        while (!check)
        {
            cin >> user.password;
            if (user.password != user.password)
            {
                cout << "密码错误！请重新输入" << endl;
                break;
            }
            else
            {
                check = 1;
                break;
            }
        }
        infile.close();
    }


    void stu_init()
    {
        fstream outfile("stu.dat", ios::out | ios::binary);
        outfile.seekp(0, ios::beg);
        outfile.write((char *)&mark, sizeof(student_dat));
        cout << "初始化完成" << endl;
        outfile.close();
    }
