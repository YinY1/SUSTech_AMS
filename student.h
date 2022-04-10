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
    void set_basic_info();
    void set_province();
    void set_student_number();
    void set_nation();
    void set_political_status();
    void set_school_name();
    bool read(char[]);
    void write(char[]);
};

struct student_dat
{
    bool check;
    char id[30];
    char student_number[50];
    char province[10];
    char nation[10];
    char political_status[30];
    char school_name[50];
    char name[30];
    char password[50];
    char phone_number[20];
};

bool endmark(student_dat);
#endif