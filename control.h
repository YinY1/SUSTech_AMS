#ifndef CONTROL_H
#define CONTROL_H

#include<windows.h>

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

#endif