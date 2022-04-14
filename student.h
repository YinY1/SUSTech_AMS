#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "control.h"
#include <fstream>
class student : public user
{
    char student_number[50]={};     //学籍号
    char province[10]={};           //省份
    char nation[10]={};             //民族
    char political_status[30]={};   //政治面貌
    char school_name[50]={};        //学校名称
    char dad_name[20]={};           //父亲姓名
    char mom_name[20]={};           //母亲姓名
    char dad_phone_number[20]={};   //父亲电话
    char mom_phone_number[20]={};   //母亲电话
    char dad_job[20]={};            //父亲职业
    char mom_job[20]={};            //母亲职业
    char dad_work_address[50]={};   //父亲工作地址
    char mom_work_address[50]={};   //母亲工作地址

public:
    student() { authority = 1; }
    void signup();
    bool login();
    void show(int);
    void set_basic_info();
    void set_province();
    void set_student_number();
    void set_nation();
    void set_political_status();
    void set_school_name();
    void set_parents_info();
    bool read(char[], int);
    void write(int);
};


bool endmark(student);
#endif