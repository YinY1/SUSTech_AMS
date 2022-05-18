#include "manager.h"
#include "base64.h"
#include <cstring>
#include <iostream>
using namespace std;

void manager::set_ukey()
{
    char key[20];
    cout << "请输入操作密码：";
    cin >> key;
    strcpy_s(ukey, key);
}

bool manager::ukey_check()
{
    cout << "请输入操作密码：" << endl;
    string key;
    cin >> key;
    return base64_encode(key) == ukey;
}