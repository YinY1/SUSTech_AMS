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

void gotoxy(HANDLE, int, int);
void middle(std::string, int);

#endif