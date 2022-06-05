#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

class student : public user
{
public:
    student();
    bool login();                    //登录
    bool confirm_password();         //确认密码
    bool change_password();          //修改密码
    bool cancel_account();           //注销账号
    bool read(char[], int);          //读取信息
    void rechieve_password();        //找回密码
    void signup();                   //注册
    void display(int);               //显示信息
    void set_email();                //设置邮箱
    void set_province();             //设置省份
    void set_security_question();    //设置安全问题
    void set_basic_info();           //设置基本信息
    void set_parents_info();         //设置家长信息
    void set_experience();           //设置工作经历
    void set_score();                //设置成绩
    void set_student_number();       //设置学籍号
    void set_nation();               //设置民族
    void set_political_status();     //设置政治面貌
    void set_school_name();          //设置学校名称
    void write(int);                 //写入信息
    void set_id();                   //设置身份证
    void set_is_admitted(int select) //设置录取状态
    {
        is_admitted = select;
    }
    void print_admitted();          //打印录取状态
    void cpy_info(const student &); //复制信息
    int input_phone_number(int);    //输入手机号
    int get_is_admitted()           //获取录取状态
    {
        return is_admitted;
    }
    float get_final_score() //获取高考成绩
    {
        return score[8][12];
    }
    float get_level_test_score() //获取等级考试成绩
    {
        return score[7][12];
    }
    void set_overall_score(float test) //设置总成绩
    {
        overall_score = ((score[8][12] / 7.5) * 0.6 + test * 0.3 + (score[7][12] / 6) * 0.1);
    }
    double get_overall_score() //获取总成绩
    {
        return overall_score;
    }
    std::string get_student_number() //获取学籍号
    {
        return student_number;
    }
    std::string get_province() //获取省份
    {
        return province;
    }
    std::string get_birthday() //获取生日
    {
        if (id[0] == '\0')
            return "";
        std::string age(id, 6, 8);
        return age;
    }
    std::string get_email() //获取邮箱
    {
        return email;
    }
    std::string get_school_name() //获取学校名称
    {
        return school_name;
    }

private:
    char email[50] = {};                    //邮箱
    char province[10] = {};                 //省份
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
    double overall_score = 0;               //总成绩
    int is_admitted = 0;                    //录取状态
};

#endif