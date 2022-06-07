#ifndef CHECK_H
#define CHECK_H

#include <string>

bool id_check(std::string);              //身份证验证
bool password_check(std::string);        //密码验证
bool province_check(std::string);        //省份验证
bool phone_check(std::string);           //手机号验证
bool nation_check(std::string);          //民族验证
bool date_check(std::string);            //日期验证
bool email_check(std::string);           //邮箱验证
int choice_check(std::string, int, int); //选择验证

#endif