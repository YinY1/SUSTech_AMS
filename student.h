#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "user.h"
using namespace std;

class student : public user
{
    static int count;        //编号
    string student_number;   //学籍号
    string province;         //省份
    string nation;           //民族
    string political_status; //政治面貌
    string school_name;      //学校名称

public:
    student();
    void signup();
    void show();
    void set_province();
    void set_student_number();
    void set_basic_info();
    void set_nation();
    void set_political_status();
    void set_school_name();
};

#endif