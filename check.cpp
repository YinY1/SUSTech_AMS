#include "check.h"
#include <iostream>

using namespace std;

// https://baike.baidu.com/item/%E8%BA%AB%E4%BB%BD%E8%AF%81%E6%A0%A1%E9%AA%8C%E7%A0%81/3800388#3_3
bool id_check(string id)
{
    if (id.length() != 18)
    {
        cerr << "\n[WRONG]身份证号码长度不符合要求，请重新输入：";
        return 0;
    }
    string map = "10X98765432";
    int ans = 0, arr[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    for (int i = 0; i < 17; i++)
        ans += (id[i] - '0') * arr[i];
    if (id[17] != map[ans % 11])
    {
        cerr << "\n[WRONG]该身份证号码不合法，请检查是否输入错误！" << endl;
        return 0;
    }
    return 1;
}

bool password_check(string password)
{
    if (password.length() > 16 || password.length() < 6 || password.find(" ") != string::npos || password.find("\n") != string::npos || password.find("\t") != string::npos || password.find("\r") != string::npos)
    {
        cout << "\n[WRONG]密码长度需要在6~16位，\n密码不能包含以下字符：空格、回车、换行、制表符!\n请重新输入：" << endl;
        return 0;
    }
    cout << "\n[INFO]请再次确认密码：";
    string password2;
    cin >> password2;
    if (password != password2)
    {
        cerr << "\n[WRONG]两次输入的密码不一致，请重新输入：";
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
    cerr << "\n[WRONG]请输入正确的省市！" << endl;
    return 0;
}

bool phone_check(string num)
{
    try
    {
        stoll(num);
        if (num.size() != 11)
            throw num;
    }
    catch (...)
    {
        cerr << "\n[WRONG]请输入正确的电话号码！输入0退出\n"
             << endl;
        cin.sync();
        return 0;
    }
    return 1;
}

bool nation_check(string nation)
{
    const char *p[] = {"汉族", "蒙古族", "回族", "藏族", "维吾尔族", "苗族", "彝族", "壮族", "布依族", "朝鲜族", "满族", "侗族", "瑶族", "白族", "土家族", "哈尼族", "哈萨克族", "傣族", "黎族", "傈僳族", "佤族", "畲族", "高山族", "拉祜族", "水族", "东乡族", "纳西族", "景颇族", "柯尔克孜族", "土族", "达斡尔族", "仫佬族", "羌族", "布朗族", "撒拉族", "毛南族", "仡佬族", "锡伯族", "阿昌族", "普米族", "塔吉克族", "怒族", "乌孜别克族", "俄罗斯族", "鄂温克族", "德昂族", "保安族", "裕固族", "京族", "塔塔尔族", "独龙族", "鄂伦春族", "赫哲族", "门巴族", "珞巴族", "基诺族"};
    for (int i = 0; i < 56; i++)
        if (nation == p[i])
            return 1;
    cerr << "\n[WRONG]请输入正确的民族！输入0退出\n"
         << endl;
    return 0;
}

bool date_check(string d) 
{
    try
    {
        if (d.size() != 8)
            throw d;
        int year = stoi(d.substr(0, 4));
        if (year > 2010 || year < 1950)
            throw year;
        int month = stoi(d.substr(4, 2));
        int day = stoi(d.substr(6, 2));
        //检查包括闰年的日期
        if (month == 2)
        {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            {
                if (day > 29)
                    throw d;
                else if (day > 28)
                    throw d;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 30)
                throw d;
        }
        else if (day > 31)
            throw d;
        else if (month > 12||month<1)
            throw d;
    }
    catch (int year)
    {
        cerr << "\n[WRONG]请输入1950~2010之间的年份！输入0退出\n"
             << endl;
        return 0;
    }
    catch (...)
    {
        cerr << "\n[WRONG]请输入正确的日期！输入0退出\n"
             << endl;
        return 0;
    }
    return 1;
}

bool email_check(string s)
{
    //邮箱合法检查
    size_t k;
    string p[] = {"@qq.com", "@163.com", "@126.com", "@sina.com", "@gmail.com", "@hotmail.com", "@sohu.com", "@139.com", "@189.com", "@wo.com.cn", "@21cn.com", "@tom.com", "@yahoo.com", "@live.com", "@msn.com", "@foxmail.com", "@yeah.net", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com", "@vip.163.com", "@vip.126.com", "@vip.yeah.net", "@vip.msn.com", "@vip.live.com", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com", "@vip.126.com", "@vip.yeah.net", "@vip.msn.com", "@vip.live.com", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com", "@vip.126.com", "@vip.yeah.net", "@vip.msn.com", "@vip.live.com", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com", "@vip.126.com", "@vip.yeah.net", "@vip.msn.com", "@vip.live.com", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com", "@vip.126.com", "@vip.yeah.net", "@vip.msn.com", "@vip.live.com", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com", "@vip.126.com", "@vip.yeah.net", "@vip.msn.com", "@vip.live.com", "@vip.qq.com", "@vip.sina.com", "@vip.tom.com"};
    for (int i = 0; i < 63; i++)
    {
        k = s.find(p[i]);
        if (k != string::npos && k == s.size() - p[i].size())
            return 1;
    }
    cerr << "\n[WRONG]请输入正确的邮箱！输入0退出\n"
         << endl;
    return 0;
}

int choice_check(string s, int min, int max)
{
    int k = -1;
    try
    {
        if (s.empty()) //当没有输入任何东西（输入了ctrl+z）时，抛出异常
        {
            cin.clear();
            cin.sync();
            throw s;
        }
        k = stoi(s);            //当选项s不为数字时，抛出异常
        if (k < min || k > max) //当选项s不在范围内时，抛出异常
            throw k;
    }
    catch (...)
    {
        cerr << "\n[WRONG]请重新输入正确的选项！\n"
             << endl;
        system("pause");
        system("cls");
        return -1;
    }
    return k;
}