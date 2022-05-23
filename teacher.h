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
    void admit();
    void signup();
    void display(int);
    void cpy_info(const teacher &);
    std::vector<student> _sort(int);
};

#endif