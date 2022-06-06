#ifndef MANAGER_H
#define MANAGER_H

#include "student.h"
#include "user.h"
#include <vector>
class manager : public user
{
public:
    bool ukey_check(); //操作密码验证
    void set_ukey();   //设置操作密码
    virtual void display(int) = 0;
    std::string get_ukey() { return ukey; } //获取操作密码
    std::vector<student> _sort(int);        //排序
protected:
    char ukey[20] = {}; //操作密码
};

#endif