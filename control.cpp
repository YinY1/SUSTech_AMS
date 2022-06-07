#include "control.h"
#include <fstream>
#include <iostream>

using namespace std;

// https://blog.csdn.net/HuangMY2007/article/details/119959021
void middle_print(string str, int y, bool mode)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOutput, &bInfo);
    int dwSizeX = bInfo.dwSize.X; //获取控制台屏幕缓冲区大小
    
    COORD pos;                            //移动光标
	if (mode == 0)
	{
		int x = dwSizeX / 2 - str.size() / 2; //获取要输出的字符串的长度
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hOutput, pos);
		cout << str << endl;
	}
	else// 打印logo
	{
		fstream f(str, ios::in);
		char c;
		int l = 12, count,x= dwSizeX / 2-30;
		while (!f.eof())
		{
			count = 0;
			pos.X = x;
			pos.Y = l++;
			SetConsoleCursorPosition(hOutput, pos);
			while (!f.eof())
			{
				c = f.get();
				cout << c;
				count++;
				if (count == 61)
					break;
			}
		}
		f.close();
	}
}

void set_window()
{
    //更改窗口标题
    SetConsoleTitleA("SCUT_AMS.beta");
    //最大化窗口
    HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, SW_MAXIMIZE);
    //固定窗口大小
    LONG_PTR sty = GetWindowLongPtrA(hwnd, GWL_STYLE);
    SetWindowLongPtrA(hwnd, GWL_STYLE, sty);
}