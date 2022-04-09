#ifndef CHECK_H
#define CHECK_H

#include <iostream>

using namespace std;

bool id_check(string id);
bool password_check(string password);
bool province_check(string province);
bool phone_check(string num);
bool nation_check(string nation);
inline void cls()
{
    system("cls");
}
inline void pause()
{
    system("pause");
}

#endif