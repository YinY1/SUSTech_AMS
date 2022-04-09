#ifndef MENU_H
#define MENU_H
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
struct userdat
{
    bool check;
    char name[20];
    char password[32];
    char phone_number[15];
};


void menu_start();
void menu_login();
void sti_init();

#endif

/* test asd asdasd
asdasd 13000000000 */