#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "manager.h"
class Administrator : public manager
{
public:
    Administrator();
    bool login();
    void search(int);
    void stu_init();
    void tea_init();
};

#endif