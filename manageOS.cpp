#include "base64.h"
#include "check.h"
#include "student.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    student s1;
    s1.signup();
    s1.set_basic_info();
    s1.show();
    pause();
    return 0;
}