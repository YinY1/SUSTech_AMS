#ifndef TEACHER_H
#define TEACHER_H

#include "manager.h"
#include "student.h"
#include <string>
#include <vector>
class teacher : public manager
{
public:
    teacher() {}
    bool login();
    bool read(char[]);	//读取数据
    void approval();	//审批
    void signup();		//注册
    void display(int);
    void input_overall_score();//录入校测成绩
    void cpy_info(const teacher &);
    std::string get_password() { return password; }
};

#endif