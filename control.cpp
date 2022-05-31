#include "control.h"
#include <iostream>
#include <windows.h>

// https://blog.csdn.net/HuangMY2007/article/details/119959021
void middle(std::string str, int y)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOutput, &bInfo);
    int dwSizeX = bInfo.dwSize.X;//获取控制台屏幕缓冲区大小
    // dwSizey = bInfo.dwSize.Y; 
    int x = dwSizeX / 2 - str.size() / 2;//获取要输出的字符串的长度
    COORD pos;//移动光标
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOutput, pos);
    std::cout << str << std::endl;
}