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
void stu_set_basic_info(student &);
void stu_rechieve_password();
void tea_login();
void admin_login();
void first_run();

int main()
{
	first_run();
	set_window();
	string choice;
	while (1)
	{
		cls();
		middle_print("---------------------", 1, 0);
		middle_print("欢迎使用管理系统!", 2, 0);
		middle_print("---------------------", 3, 0);
		cout << "\n[INFO]请按照提示输入选项\n\n"
			 << "1.学生注册\n\n2.学生登录\n\n3.教师登录\n\n"
			 << "4.找回密码(学生)\n\n5.报考指南\n\n0.退出\n"
			 << endl;
		cin >> choice;
		if (choice == "admin")
			choice = "6";
		int c = choice_check(choice, 0, 6);
		cls();
		switch (c)
		{
		case 1:
			stu_signup();
			break;
		case 2:
			stu_login();
			break;
		case 3:
			tea_login();
			break;
		case 4:
			stu_rechieve_password();
			break;
		case 5:
			middle_print("data\\kal.txt", 1, 1);
			cout << "no guidence";
			pause();
			break;
		case 6:
			admin_login();
			break;
		case 0:
			middle_print("data\\kal.txt", 1, 1); //打印logo
			cout << "欢迎再次使用:D" << endl;
			Sleep(1000);
			exit(0);
		default:
			cin.sync();
			continue;
		}
	}
}

void first_run()
{
	admin a;
	fstream f("data\\student.dat", ios::in), g("data\\teacher.dat", ios::in), h("data\\admission_list.txt", ios::in);
	if (!f)
	{
		f.close();
		a.stu_init();
	}
	if (!g)
	{
		g.close();
		a.tea_init();
	}
	if (!h)
	{
		h.close();
		h.open("data\\admission_list.txt", ios::out);
		h.close();
	}
}

void stu_login()
{
	student stu;
	if (stu.login())
	{
		bool flag = 1;
		string choice, s;
		while (flag)
		{
			cls();
			s = " 欢迎您," + stu.get_name() + "同学!";
			middle_print("-----------------------", 1, 0);
			middle_print(s, 2, 0);
			middle_print("-----------------------", 3, 0);
			if (stu.get_is_admitted() == 0)
			{
				cout << "\n[INFO]请按照提示输入选项\n\n"
					 << "1.查看\\修改个人基本信息\n\n2.查看\\修改家庭成员信息\n\n3.查看\\填写个人经历\n\n4.查看\\填写成绩\n\n5.设置密保问题\n\n6.修改密码\n\n7.删除账户\n\n0.退出登录\n " << endl;
				cin >> choice;
				int c = choice_check(choice, 0, 7);
				cls();
				switch (c)
				{
				case 1:
					stu.display(1);
					stu_set_basic_info(stu);
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
					cin.sync();
					continue;
				}
				cls();
				cout << "\n\n[INFO]已成功登出！\n"
					 << endl;
			}
			else if (stu.get_is_admitted() == 1)
			{
				fstream f("data\\admission_list.txt", ios::in);
				string s;
				f >> s;
				if(s!="姓名")
				{
				middle_print("-------------------------------", 1, 0);
				middle_print("您的资料已通过初审，请准备考试", 2, 0);
				middle_print("-------------------------------", 3, 0);
				stu.print_exam_info();
				}
				else
				{
					bool flag = 0;
					while(!f.eof())
					{
						f >> s;
						if(s==stu.get_name())
						{
							middle_print("-------------------------------", 5, 0);
							middle_print("恭喜你已被录取", 6, 0);
							middle_print("-------------------------------", 7, 0);
							flag = 1;
							break;
						}
					}
					if(!flag)
					{
						middle_print("-------------------------------", 5, 0);
						middle_print("很遗憾，您未被录取", 6, 0);
						middle_print("-------------------------------", 7, 0);
					}
				}
				pause();
				break;
			}
			else
			{
				middle_print("--------------------------", 1, 0);
				middle_print("很遗憾，您未通过初审", 2, 0);
				middle_print("--------------------------", 3, 0);
				pause();
				break;
			}
		}
		sleep();
		cls();
	}
}

void stu_signup()
{
	//判断报名是否截止
	fstream f("data\\admission_list.txt", ios::in);
	if(f.get()!=EOF)
	{
		cout << "\n[INFO]报名已截止！" << endl;
		pause();
		return;
	}
	student stu;
	stu.signup();
	cout << endl;
	pause();
	cout << "\n[INFO]返回菜单ing" << endl;
	sleep();
}

void stu_set_basic_info(student &stu)
{
	string choice;
	while (1)
	{
		cout << "\n[INFO]请输入想要更改的信息：\n1.学校名称\n2.民族\n3.政治面貌\n4.高考省份\n5.学籍号\n6.身份证\n7.邮箱\n8.显示目前信息\n0.退出\n"
			 << endl;
		cin >> choice;
		int c = choice_check(choice, 0, 8);
		switch (c)
		{
		case 1:
			stu.set_school_name();
			break;
		case 2:
			stu.set_nation();
			break;
		case 3:
			stu.set_political_status();
			break;
		case 4:
			stu.set_province();
			break;
		case 5:
			stu.set_student_number();
			break;
		case 6:
			stu.set_id();
			break;
		case 7:
			stu.set_email();
			break;
		case 8:
			stu.display(1);
			pause();
			break;
		case 0:
			cls();
			if (stu.get_id() == "")
				cout << "\n[INFO]如果未填写身份证号码将无法通过审批！请尽快补全资料\n"
					 << endl;
			pause();
			cls();
			stu.write(1);
			return;
		default:
			cin.sync();
			continue;
		}
	}
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
		string choice, s;
		while (1)
		{
			cls();
			s = " 欢迎您," + t.get_name() + "老师!";
			middle_print("-----------------------", 0, 0);
			middle_print(s, 1, 0);
			middle_print("-----------------------", 2, 0);
			cout << "[INFO]请按照提示输入选项\n\n"
				 << "1.按姓名查找\n2.按学籍号查找\n3.按学校代码查找\n4.按出生时间段查找\n5.按分数段查找\n\n"
				 << "6.列出还未审核的学生\n7.列出已过审的学生\n8.列出未过审的学生\n\n"
				 << "9.按姓名排序\n10.按成绩排序\n11.按省份排序\n12.按年龄排序\n\n"
				 << "13.进行审批\n14.登记校测成绩\n\n0.退出" << endl;
			cin >> choice;
			int c = choice_check(choice, 0, 14);
			cls();
			switch (c)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				t.display(c);
				pause();
				break;
			case 9:
			case 10:
			case 11:
			case 12:
			{
				vector<student> vs = t._sort(c - 8);
				for (auto i : vs)
					cout << "\n"
						 << i.get_name() << "\n  生源： " << i.get_province() << "\n  总分 " << i.get_final_score() << "\n 出生日期:" << i.get_birthday() << endl;
				cout << "\n\n[INFO]共有 " << vs.size() << " 个学生\n"
					 << endl;
				pause();
				break;
			}
			case 13:
				t.approval();
				pause();
				break;
			case 14:
				t.input_overall_score();
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
				cin.sync();
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
		string choice;
		while (1)
		{
			cls();
			cout << "choice:\n"
				 << "1.display teacher(s) info by name\n"
				 << "2.display teacher(s) info in id order\n"
				 << "3.initialize students data\n"
				 << "4.initialize teachers data\n"
				 << "5.register teachers accounts\n"
				 << "6.admit\n"
				 <<"7.stop register\n"
				 << "0.exit" << endl;
			cin >> choice;
			int c = choice_check(choice, 0, 7);
			cls();
			switch (c)
			{
			case 1:
			case 2:
				a.display(c);
				pause();
				break;
			case 3:
				if (a.ukey_check())
				{
					a.stu_init();
					cout << "\nInitialization \"student.dat\" complete" << endl;
				}
				else
					cout << "ukey error" << endl;
				pause();
				break;
			case 4:
				if (a.ukey_check())
				{
					a.tea_init();
					cout << "\nInitialization \"teacher.dat\" complete" << endl;
				}
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
				}
				else
					cout << "ukey error" << endl;
				break;
			}
			case 6:
			{
				if (a.ukey_check())
					a.admit();
				else
				{
					cout << "ukey error" << endl;
					pause();
				}
				break;
			}
			case 7:
				if (a.ukey_check())
					a.deadline();
				else
				{
					cout << "ukey error" << endl;
					pause();
				}
				break;
			case 0:
				return;
			default:
				cin.sync();
				continue;
			}
		}
	}
	else
		cout << "WRONG" << endl;
}