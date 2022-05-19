#ifndef TEACHER_H
#define TEACHER_H

#include "manager.h"
#include "student.h"
#include <vector>
class teacher : public manager
{
public:
    teacher() {}
    void signup();
    bool login();
    bool read(char[]);
    void admit();
    void show(int);
    std::vector<student> _sort(int);
    void cpy_info(const teacher &);
};

#endif