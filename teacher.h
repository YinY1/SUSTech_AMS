#ifndef TEACHER_H
#define TEACHER_H

#include "manager.h"
#include "student.h"
#include <vector>
class teacher : public manager
{
    char college[50] = {};//学院
public:
    teacher() {}
    void signup();
    bool login();
    bool read(char[]);
    void admit();
    void search(int);
    std::vector<student> _sort(int);
    void cpy_info(const teacher &);
};

#endif