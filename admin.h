#ifndef ADMIN_H
#define ADMIN_H

#include "manager.h"
class admin : public manager
{
public:
    admin();
    bool login();
    void display(int);
    void stu_init();	//初始化学生信息
    void tea_init();	//初始化教师信息
    void admit();		//录取
	void deadline();	//截止报名
};

#endif