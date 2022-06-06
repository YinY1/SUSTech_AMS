#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <windows.h>
inline void cls()
{
    system("cls");
}
inline void pause()
{
    system("pause");
}
inline void sleep()
{
    Sleep(500);
}

void middle_print(std::string, int,bool); //居中打印
void set_window();             //设置窗口

#endif