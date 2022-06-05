#ifndef TEACHER_H
#define TEACHER_H

#include "manager.h"
#include "student.h"
#include <vector>
class teacher : public manager
{
public:
    teacher() {}
    bool login();
    bool read(char[]);
    void approval(); //审批
    void signup();   //注册
    void display(int);
    void cpy_info(const teacher &);
};

#endif