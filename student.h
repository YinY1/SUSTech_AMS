#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "control.h"
#include <fstream>
class student : public user
{
    std::string student_number;   //学籍号
    std::string province;         //省份
    std::string nation;           //民族
    std::string political_status; //政治面貌
    std::string school_name;      //学校名称
    std::string dad_name;         //父亲姓名
    std::string mom_name;         //母亲姓名
    std::string dad_phone_number; //父亲电话
    std::string mom_phone_number; //母亲电话
    std::string dad_job;          //父亲职业
    std::string mom_job;          //母亲职业
    std::string dad_work_address;   //父亲工作单位
    std::string mom_work_address;   //母亲工作单位

public:
    student();
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

struct student_dat
{
    char phone_number[20];
    char id[30];
    char student_number[50];
    char province[10];
    char nation[10];
    char political_status[30];
    char school_name[50];
    char name[30];
    char password[50];
    char dad_name[20];
    char mom_name[20];
    char dad_phone_number[20];
    char mom_phone_number[20];
    char dad_job[20];
    char mom_job[20];
    char dad_work_address[50];
    char mom_work_address[50];
};

bool endmark(student_dat);
#endif