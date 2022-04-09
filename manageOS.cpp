#include "check.h"
#include "student.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

inline void clear_screen()
{
    cout << "\033[2J\033[1;1H";
}
int main()
{
    student s1;
    s1.signup();
    s1.set_basic_info();
    s1.show();
    system("pause");
    return 0;
}