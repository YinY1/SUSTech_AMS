#include "manager.h"
#include "base64.h"
#include <cstring>
#include <iostream>
using namespace std;

void manager::set_ukey()
{
    char ukey[20];
    cout << "请输入操作密码：";
    cin >> ukey;
    strcmp(this->ukey, base64_encode(ukey).c_str());
}

bool manager::ukey_check()
{
    cout << "请输入操作密码：" << endl;
    string key;
    cin >> key;
    return base64_encode(key) == ukey;
}