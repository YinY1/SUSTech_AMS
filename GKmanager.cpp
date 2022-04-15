#include "admin.h"
#include "student.h"

using namespace std;

void stu_init();

int main()
{
    while (1)
    {
        int choice;
        cls();
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
                if (stu.login())
                {
                    cout << "请选择你要进行的操作：\n1.查看\\修改个人基本信息\t2.查看\\修改家庭成员信息\t0.退出登录" << endl;
                    int select, flag = 1;
                    while (cin >> select)
                    {
                        switch (select)
                        {
                        case 0:
                            flag = 0;
                            break;
                        case 1:
                            stu.show(0);
                            stu.set_basic_info();
                            break;
                        case 2:
                            stu.show(1);
                            stu.set_parents_info();
                            break;
                        }
                        if (flag == 0)
                            break;
                        cout << "请选择你要进行的操作：\n1.查看\\修改个人基本信息\t2.查看\\修改家庭成员信息\t0.退出登录" << endl;
                    }
                    cls();
                    cout << "已成功登出！" << endl;
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
                cls();
            default:
                break;
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
}
