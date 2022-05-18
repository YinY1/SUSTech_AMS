#include"check.h"
#include <iostream>

using namespace std;

bool id_check(string id)
{
    if (id.length() != 18)
    {
        cout << "身份证号码长度不符合要求，请重新输入：";
        return 0;
    }

    string map = "10X98765432";
    int ans = 0, arr[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    for (int i = 0; i < 17; i++)
        ans += (id[i] - '0') * arr[i];
    if (id[17] != map[ans % 11])
    {
        cout << "该身份证号码不合法，请检查是否输入错误！" << endl;
        return 0;
    }
    return 1;
    // test_id:34052419800101001X
}

bool password_check(string password)
{
    if (password.length() > 16 || password.length() < 6)
    {
        cout << "密码长度不符合要求，请重新输入：";
        return 0;
    }
    if (password.find(" ") != string::npos || password.find("\n") != string::npos || password.find("\t") != string::npos || password.find("\r") != string::npos)
    {
        cout << "密码不能包含以下字符：空格、回车、换行、制表符!请重新输入!" << endl;
        return 0;
    }
    cout<<"请再次确认密码：";
    string password2;
    cin >> password2;
    if (password != password2)
    {
        cout << "两次输入的密码不一致，请重新输入：";
        return 0;
    }
    return 1;
}

bool province_check(string province)
{
    const char *p[] = {"北京", "上海", "天津", "重庆", "河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南", "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾", "内蒙古", "广西", "西藏", "宁夏", "新疆", "香港", "澳门"};
    for (int i = 0; i < 34; i++)
        if (province == p[i])
            return 1;
    cout << "请输入正确的省市！" << endl;
    return 0;
}

bool phone_check(string num)
{
    if (num.size() != 11)
    {
        cout << "手机号码有误，请重新输入：";
        return 0;
    }
    return 1;
}//test num:18688888888

bool nation_check(string nation)
{
    //民族
    const char *p[]={"汉族","蒙古族","回族","藏族","维吾尔族","苗族","彝族","壮族","布依族","朝鲜族","满族","侗族","瑶族","白族","土家族","哈尼族","哈萨克族","傣族","黎族","傈僳族","佤族","畲族","高山族","拉祜族","水族","东乡族","纳西族","景颇族","柯尔克孜族","土族","达斡尔族","仫佬族","羌族","布朗族","撒拉族","毛南族","仡佬族","锡伯族","阿昌族","普米族","塔吉克族","怒族","乌孜别克族","俄罗斯族","鄂温克族","德昂族","保安族","裕固族","京族","塔塔尔族","独龙族","鄂伦春族","赫哲族","门巴族","珞巴族","基诺族"};
    for (int i = 0; i < 56; i++)
        if (nation == p[i])
            return 1;
    cout<<"请输入正确的民族！"<<endl;
    return 0;
}

bool college_check(string college)
{
    //学院
    const char *p[] = {"理学院", "工学院","医学院","商学院","人文社科学院","生命科学学院","设计学院"};
    for (int i = 0; i < 7; i++)
        if (college == p[i])
            return 1;
    cout << "请输入正确的学院！" << endl;
    return 0;
}