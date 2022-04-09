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

struct student_dat
{
    bool check;
    char student_number[30];
    char province[10];
    char nation[10];
    char political_status[15];
    char school_name[50];
    char name[20];
    char password[32];
    char phone_number[15];
};

bool endmark(student_dat);
#endif