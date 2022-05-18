#ifndef ADMIN_H
#define ADMIN_H

#include "manager.h"
class admin : public manager
{
public:
    admin();
    bool login();
    void show(int);
    void stu_init();
    void tea_init();
};

#endif