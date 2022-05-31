#ifndef CHECK_H
#define CHECK_H

#include <string>

bool id_check(std::string);
bool password_check(std::string);
bool province_check(std::string);
bool phone_check(std::string);
bool nation_check(std::string);
bool date_check(std::string);
bool email_check(std::string);
int choice_check(std::string, int, int);

#endif