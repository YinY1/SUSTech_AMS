#include "control.h"
#include <iostream>
#include <windows.h>

// https://blog.csdn.net/HuangMY2007/article/details/119959021
void gotoxy(HANDLE hOut, int x, int y) //移动光标
{
    COORD pos;
    pos.X = x; //横坐标
    pos.Y = y; //纵坐标
    SetConsoleCursorPosition(hOut, pos);
}
void middle(std::string str, int y)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOutput, &bInfo);
    int dwSizeX = bInfo.dwSize.X;
    // dwSizey = bInfo.dwSize.Y; //获取控制台屏幕缓冲区大小
    int len = str.size(); //获取要输出的字符串的长度
    int x = dwSizeX / 2 - len / 2;
    gotoxy(hOutput, x, y); //移动光标
    std::cout << str << std::endl;
}