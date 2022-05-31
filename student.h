#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

class student : public user
{
    char email[50] = {};
    char province[10] = {};
    char gender[5] = {};                    //性别
    char student_number[50] = {};           //学籍号                //省份
    char nation[10] = {};                   //民族
    char political_status[30] = {};         //政治面貌
    char school_name[50] = {};              //学校名称
    char dad_name[20] = {};                 //父亲姓名
    char mom_name[20] = {};                 //母亲姓名
    char dad_phone_number[20] = {};         //父亲电话
    char mom_phone_number[20] = {};         //母亲电话
    char dad_job[20] = {};                  //父亲职业
    char mom_job[20] = {};                  //母亲职业
    char dad_work_address[50] = {};         //父亲工作地址
    char mom_work_address[50] = {};         //母亲工作地址
    char experience[6][1005] = {};          //中学经历
    char security_question[55] = {"empty"}; //密保问题
    char security_answer[25] = {};          //密保答案
    char application[5][20] = {};           //志愿
    float score[9][13] = {};                //成绩
    int is_admitted = 0;                    //是否录取
public:
    student();
    bool login();
    bool confirm_password();
    bool change_password();
    bool cancel_account();
    bool read(char[], int);
    void rechieve_password();
    void signup();
    void display(int);
    void set_email();
    void set_province();
    void set_security_question();
    void set_basic_info();
    void set_parents_info();
    void set_experience();
    void set_score();
    void set_student_number();
    void set_nation();
    void set_political_status();
    void set_school_name();
    void write(int);
    void set_id();
    void set_is_admitted(int select) { is_admitted = select; }
    void print_admitted();
    void cpy_info(const student &);
    int input_phone_number(int);
    int get_is_admitted() { return is_admitted; }
    float get_score() //获取高考成绩
    {
        return score[8][12];
    }
    std::string get_student_number()
    {
        return student_number;
    }
    std::string get_province()
    {
        return province;
    }
    std::string get_birthday()
    {
        if(id[0]=='\0') return "";
        std::string age(id,6,8);
        return age;
    }
    std::string get_email()
    {
        return email;
    }
    std::string get_school_name()
    {
        return school_name;
    }
};

#endif