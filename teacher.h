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
    bool read(char[]);//��ȡ����
    void approval(); //����
    void signup();   //ע��
    void display(int);
    void set_overall_score(float);
    void cpy_info(const teacher &);
    std::string get_password() { return password; }
};

#endif