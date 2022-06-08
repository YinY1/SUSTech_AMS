#include "student.h"
#include "base64.h"
#include "check.h"
#include "control.h"
#include <fstream>
#include <iomanip>
#include <iostream>

//包含windows.h前使用std会导致byte重定义https://github.com/msys2/MINGW-packages/issues/7035
//所以不要在头文件using,实在不想打std::可以在cpp里面using，尽量不要using namespace，除非确定没有重复。
using namespace std;

const student mark = student();

void student::signup()
{
    middle_print("---------------------", 1,0);
    middle_print("欢迎使用管理系统!", 2,0);
    middle_print("---------------------", 3,0);
    cout << "\n[INFO]请按照提示进行注册\n\n";
    strcpy_s(phone_number, set_phone_number().c_str());
    //查重
    if (strcmp(phone_number, "0") == 0)
        return;
    if (read(phone_number, 0))
    {
        cerr << "\n[WRONG]用户已存在！\n"
             << endl;
        return;
    }
    else
        write(0);
}

int student::input_phone_number(int read_flag)
{
    char key[15];
    cout << "\n[INFO]请输入手机号：\t 输入0返回\n"
         << endl;
    cin >> key;
    if (key[0] == '0')
        return 0;
    if (read(key, read_flag))
        return 1;
    return -1;
}

bool student::login()
{
    while (1)
    {
        switch (input_phone_number(1))
        {
        case 0:
            return 0;
        case 1:
            sleep();
            cls();
            return 1;
        case -1:
            cerr << "\n[WRONG]用户不存在！请重新输入账号！\t输入0返回" << endl;
        }
    }
    return 0;
}

void student::set_email()
{
    string email;
    cout << "\n[INFO]请输入邮箱：\t 输入0返回\n"
         << endl;
    while (1)
    {
        cin >> email;
        if (email == "0")
            return;
        if (email_check(email))
        {
            strcpy_s(this->email, email.c_str());
            break;
        }
    }
}

void student::set_province()
{
    string province;
    bool check = 0;
    cout << "\n[INFO]请输入省份（地区）：" << endl;
    while (!check)
    {
        cin >> province;
        check = province_check(province); //判断省份是否合法
    }
    strcpy_s(this->province, province.c_str());
}

void student::set_id()
{
    string id;
    bool check = 0;
    cout << "\n[INFO]请输入身份证号码：\n"
         << endl;
    while (!check)
    {
        cin >> id;
        check = id_check(id); //判断身份证号码是否合法
    }
    strcpy_s(this->id, id.c_str());
    if (id[17] % 2) //判断性别,身份证第17位为奇数为男，偶数为女
        strcpy_s(this->gender, "男");
    else
        strcpy_s(this->gender, "女");
}

void student::set_student_number()
{
    cout << "\n[INFO]请输入学籍号：\n"
         << endl;
    cin >> student_number;
}

void student::set_nation()
{
    string nation;
    bool check = 0;
    cout << "\n[INFO]请输入民族：\n格式：XX族，如“汉族”\n"
         << endl;
    while (!check)
    {
        cin >> nation;
        check = nation_check(nation); //判断民族是否合法
    }
    strcpy_s(this->nation, nation.c_str());
}

void student::set_school_name()
{
    string school_name;
    while (1)
    {
        cout << "\n[INFO]请输入学校名称：\n"
             << endl;
        cin >> school_name;
        if (school_name.length() < 45)
        {
            strcpy_s(this->school_name, school_name.c_str());
            break;
        }
        else
        {
            cerr << "\n[WRONG]学校名称过长！请重新输入！\n"
                 << endl;
        }
    }
    strcpy_s(this->school_name, school_name.c_str());
}

void student::set_political_status()
{
    string num;
    //政治面貌
    const char *p[] = {"中共党员", "中共预备党员", "共青团员", "民革党员", "民盟盟员", "民建会员", "民进会员", "农工党党员", "致公党党员", "九三学社社员", "台盟盟员", "无党派人士", "群众"};
    cout << "\n[INFO]请输入政治面貌：\n\n1.中共党员\t2.中共预备党员\t3.共青团员\t4.民革党员\n\n5.民盟盟员\t6.民建会员\t7.民进会员\t8.农工党党员\n\n9.致公党党员\t10.九三学社社员\t11.台盟盟员\t12.无党派人士\t13.群众\n"
         << endl;
    while (1)
    {
        cin >> num;
        int n = choice_check(num, 1, 13);
        if (n == -1)
        {
            pause();
            cin.sync();
            continue;
        }
        strcpy_s(political_status, p[n - 1]);
        break;
    }
}

void student::set_parents_info()
{

    string choice;
    while (1)
    {
        cout << "\n[INFO]\n请选择需要填写的信息：\n"
             << "1.父亲姓名\t2.母亲姓名\t3.父亲联系方式\t4.母亲联系方式\n"
             << "5.父亲工作地址\t6.母亲工作地址\t7.父亲职业\t8.母亲职业\t9.显示家长信息\n0.返回" << endl;
        cin >> choice;
        int c = choice_check(choice, 0, 9);
        switch (c)
        {
        case 1:
            cout << "\n[INFO]请输入父亲姓名：\n"
                 << endl;
            cin >> dad_name;
            break;
        case 2:
            cout << "\n[INFO]请输入母亲姓名：\n"
                 << endl;
            cin >> mom_name;
            break;
        case 3:
            strcpy_s(dad_phone_number, set_phone_number().c_str());
            break;
        case 4:
            strcpy_s(mom_phone_number, set_phone_number().c_str());
            break;
        case 5:
            cout << "\n[INFO]请输入父亲工作地址：\n"
                 << endl;
            cin >> dad_work_address;
            break;
        case 6:
            cout << "\n[INFO]请输入母亲工作地址：\n"
                 << endl;
            cin >> mom_work_address;
            break;
        case 7:
            cout << "\n[INFO]请输入父亲职业：\n"
                 << endl;
            cin >> dad_job;
            break;
        case 8:
            cout << "\n[INFO]请输入母亲职业：\n"
                 << endl;
            cin >> mom_job;
            break;
        case 9:
            display(2);
            pause();
            break;
        case 0:
            write(2);
            cls();
            return;
        default:
            pause();
            cin.sync();
            continue;
        }
    }
}

void student::set_experience()
{
    string choice;
    const string p = "\n[INFO]请输入你的中学经历：（回车结束输入，用空格隔开不同的项目）\n格式如下：\n学校名称\t阶段\t入学时间-毕业/转校时间\t，担任职务/获得奖项\nXXXX中学，初中/，20XX-20XX，班长，三好学生，学习之星\nXXXX学校,高中，20XX-20XX，班长，三好学生，学习之星\n请不要超过500字！！！\n";
    while (1)
    {
        cout << "\n[INFO]请选择需要进行的操作：\n"
             << "1.删除/修改经历\t2.查看经历\n"
             << "0.返回" << endl;
        cin >> choice;
        int c = choice_check(choice, 0, 3);
        if (c == -1)
        {
            cin.sync();
            continue;
        }
        switch (c)
        {
        case 1:
            while (1)
            {
                cls();
                display(3);
                cout << "\n[INFO]请输入需要操作的序号（输入0退出）：\n"
                     << endl;
                string index, select;
                cin >> index;
                int i = choice_check(index, 0, 6);
                if (i == -1)
                {
                    pause();
                    continue;
                }
                if (i == 0)
                    break;
                else
                {
                    cout << "\n[INFO]删除请输入1，修改请输入2：\n"
                         << endl;
                    cin >> select;
                    int s = choice_check(select, 1, 2);
                    if (s == -1)
                    {
                        cin.sync();
                        continue;
                    }
                    if (s == 1)
                        strcpy_s(experience[i - 1], "");
                    else
                    {
                        cls();
                        cout << "\n[INFO]请输入新的经历:\n"
                             << p << endl;
                        string exp;
                        cin.ignore();
                        getline(cin, exp);
                        if (exp == "0")
                        {
                            cls();
                            break;
                        }
                        if (exp.size() > 500)
                            cout << "\n[INFO]输入长度超过500字,请减小长度后再试!\n"
                                 << endl;
                        else
                            strcpy_s(experience[i - 1], exp.c_str());
                    }
                    pause();
                }
            }
            break;
        case 2:
            display(3);
            pause();
            break;
        case 0:
            cls();
            cout << "\n[SUCCESS]输入完成！正在返回……" << endl;
            write(3);
            sleep();
            return;
        default:
            cerr << "\n[WRONG]输入错误，请重新输入：" << endl;
            break;
        }
    }
}

void student::set_security_question()
{
    string s;
    if (base64_decode("empty") == security_question)
        cout << "\n[INFO]还未设置密保问题！" << endl;
    else
        cout << "\n[INFO]当前密保问题为:\n"
             << security_question << endl;
    cout << "\n[INFO]请输入你想设置的密保问题(25汉字/50英文字符以内)：\n\n输入0返回" << endl;
    while (1)
    {
        cin >> s;
        if (s == "0")
        {
            cls();
            return;
        }
        if (s.length() < 50)
        {
            strcpy_s(this->security_question, s.c_str());
            break;
        }
        else
            cerr << "\n[WRONG]密保问题过长，请重新输入：" << endl;
    }
    cout << "\n[INFO]请输入你想设置的密保答案(10汉字/20英文字符以内)：\n\n输入0返回" << endl;
    while (1)
    {
        cin >> s;
        if (s == "0")
        {
            cls();
            return;
        }
        if (s.length() < 20)
        {
            strcpy_s(this->security_answer, s.c_str());
            break;
        }
        else
            cerr << "\n[WRONG]密保答案过长，请重新输入：" << endl;
    }
    cls();
    cout << "\n[INFO]设置完成！您的密保为：\n"
         << "\n问题：\t" << security_question << "\n"
         << "\n答案：\t" << security_answer << endl;
    write(9);
    pause();
}

void student::rechieve_password()
{
    cls();
    int flag = 1;
    while (flag)
    {
        int p = input_phone_number(3);
        switch (p)
        {
        case -1:
            cls();
            cerr << "\n[WRONG]用户不存在！" << endl;
            break;
        case 0:
            cls();
            return;
        case 1:
            flag = 0;
        }
    }
    string ans;
    if (strcmp(security_question, "empty") == 0)
    {
        cout << "\n[INFO]您没有设置密保！\n"
             << endl;
        pause();
        cls();
        return;
    }
    cout << "\n[INFO]请回答以下问题：\n"
         << base64_decode(security_question) << endl;
    cout << "\n[INFO]请输入密保答案：\n"
         << endl;
    while (cin >> ans)
    {
        if (ans == base64_decode(security_answer))
        {
            cout << "\n[INFO]答案正确！下面将进行密码重置！\n"
                 << endl;
            set_password();
            break;
        }
        else
            cerr << "\n[WRONG]密保答案错误，请重新输入：\n"
                 << endl;
    }
    cout << "\n[SUCCESS]密码修改成功！\n"
         << endl;
    write(5);
}

void student::set_score()
{
    string select;
    const char *test[] = {"高一上期末考", "高一下期末考", "高二上期末考", "高二下期末考", "高三模拟考一（校级以上）", "高三模拟考二（校级以上）", "高三模拟考三（校级以上）", "学业水平考试", "高考"};
    while (1)
    {
        cout << "\n请选择需要进行的操作：\n"
             << "1.填写成绩\t2.查看成绩\t"
             << "0.返回" << endl;
        cin >> select;
        int s = choice_check(select, 0, 2);
        if (s == -1)
        {
            pause();
            cin.sync();
            continue;
        }
        switch (s)
        {
        case 1:
        {
            string choice;
            while (1)
            {
                cls();
                cout << "\n请选择需要填写的成绩：\n"
                     << "1.高一上期末考\n2.高一下期末考\n3.高二上期末考\n4.高二下期末考\n"
                     << "5.高三模拟考一（校级以上）\n6.高三模拟考二（校级以上）\n7.高三模拟考三（校级以上）\n8.学业水平考试\n9.高考\n0.返回\n"
                     << endl;
                cin >> choice;
                int c = choice_check(choice, 0, 9);
                if (c == -1)
                {
                    pause();
                    cin.ignore(100, '\n');
                    continue;
                }
                if (c == 0)
                {
                    cls();
                    break;
                }
				
                const char *p[] = {"语文", "数学", "外语", "物理", "化学", "生物", "地理", "政治", "历史", "技术", "年级排名", "年级总人数"};
                if (c == 8)
                    cout << "\n[INFO]等级A输入100，等级B输入80，等级C输入60，等级D输入40，等级E/(无等级)输入0\n";
                else
                    cout << "\n[INFO]请输入你的成绩，没有的请填0（总分750分制）：\n";
                cout << "请输入 " << test[c - 1] << " 成绩：" << endl;
				
				double former_score[13];//保存更改前的分数
				for (int i = 0; i < 13; i++)
				{
					former_score[i] = score[c - 1][i];
					score[c - 1][i] = 0;
				}
                
				if (c == 8)//学业水平考试另外计算
                {
                    for (int i = 3,temp; i <= 8; i++)
                    {
                        cout << "\n"
                             << p[i] << "\t";
                        cin >> temp;
                        if (temp != 100 && temp != 80 && temp != 60 && temp != 40 && temp != 0)
                        {
                            cerr << "\n[WRONG]输入错误，请重新输入：\n"
                                 << endl;
                            i--;
                            continue;
                        }
                        score[c - 1][i] = temp;
                        score[c - 1][12] += temp;
                    }
                }
                else
                {
                    for (int i = 0; i < 12; i++)
                    {
                        if(c==9&&i>9)//高考成绩不需要看年级排名，剔除
                            break;
                        cout << "\n"
                             << p[i] << "\t";
                        cin >> score[c - 1][i];
                        if (i < 10)
                            score[c - 1][12] += score[c - 1][i]; //计算总分
                        if (score[c - 1][12] > 750)
                        {
                            cerr << "\n[WRONG]你的总分超过了750分，请检查输入！\n"
                                 << endl;
                            pause();
                            for(int i=0;i<13;i++)
								score[c - 1][i]=former_score[i];
                            break;
                        }
                    }
                }
                cout << "\n\n[INFO]输入完成！" << endl;
                pause();
            }
            pause();
            break;
        }
        case 2:
            display(4);
            pause();
            break;
        case 0:
            cls();
            write(4);
            return;
        default:
            cout << "输入错误，请重新输入：" << endl;
        }
        cls();
    }
}

void student::set_exam_info()
{
    string n=this->name,str[4];
    str[0] = "姓名：" + n;
    n = this->id;
    str[1]="身份证：" + n;
    size_t num=time(0)%10000000+stoi(get_birthday());
    str[2]="准考证号：" + to_string(num);
    str[3]="考试时间：15：00-17：30";
    for(int i=0;i<4;i++)
        strcpy_s(exam_info[i],str[i].c_str());
}

void student::print_exam_info()
{
    for(int i=0;i<4;i++)
        middle_print(exam_info[i],i+4,0);
}

void student::display(int choice)
{
    switch (choice)
    {
    case 1:
        cout << "\n姓名：" << name
             << "\n性别：" << gender
             << "\n学籍号：" << student_number
             << "\n身份证号码：" << id
             << "\n高考省份（地区）：" << province
             << "\n手机号码：" << base64_decode(phone_number)
             << "\n民族：" << nation
             << "\n政治面貌：" << political_status
             << "\n学校名称：" << school_name
             << "\n邮箱地址：" << email << "\n"
             << endl;
        break;
    case 2:
        cout << "\n父亲姓名:" << dad_name
             << "\n父亲电话:" << dad_phone_number
             << "\n父亲职业:" << dad_job
             << "\n父亲工作地址:" << dad_work_address
             << "\n母亲姓名:" << mom_name
             << "\n母亲电话:" << mom_phone_number
             << "\n母亲职业:" << mom_job
             << "\n母亲工作地址:" << mom_work_address
             << endl;
        break;
    case 3:
        cout << "个人经历：" << endl;
        for (int i = 0; i < 6; i++)
            cout << i + 1 << ". " << experience[i] << endl;
        break;
    case 4:
    {
        string s;
        cout << "\n[INFO]请输入你想查看的成绩:\n"
             << "1.高一上期末考\n2.高一下期末考\n3.高二上期末考\n4.高二下期末考\n"
             << "5.高三模拟考一（校级以上）\n6.高三模拟考二（校级以上）\n7.高三模拟考三（校级以上）\n8.学业水平考试\n9.高考\n0.返回\n"
             << endl;
        cin >> s;
        int c = choice_check(s, 0, 9);
        if (c == -1)
        {
            cin.sync();
            return;
        }
        if (c == 0)
        {
            cls();
            break;
        }
        const char *p[] = {"语文", "数学", "外语", "物理", "化学", "生物", "地理", "政治", "历史", "技术", "年级排名", "年级总人数", "总分"};
        for (int i = 0; i < 13; i++)
            cout << setiosflags(ios::left) << setw(10) << p[i] << score[c - 1][i] << endl;
        break;
    }
    }
}

bool student::read(char key[], int choice)
{
    student r;
    string ekey = base64_encode(key);
    fstream f("data\\student.dat", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    do
    {
        f.read((char *)&r, sizeof(r));
    } while (ekey != r.phone_number && !endmark(r));
    if (ekey != r.phone_number)
    {
        f.close();
        return 0; //没有重复
    }
    switch (choice)
    {
    case 0: //用作注册时单纯查询账号
        break;
    case 1: //用作登录时同时检查密码
    {
        string pass;
        cout << "\n[INFO]请输入密码：\n"
             << endl;
        while (cin >> pass)
        {
            if (strcmp(base64_encode(pass).c_str(), r.password) == 0)
            {
                cout << "\n[SUCCESS]登录成功！\n"
                     << endl;
                this->cpy_info(r); //读取信息
                break;
            }
            cerr << "\n[WRONG]密码错误，请重新输入：\n"
                 << endl;
        }
        break;
    }
    case 3: //用作查询密保
        strcpy_s(security_question, r.security_question);
        strcpy_s(security_answer, r.security_answer);
        strcpy_s(phone_number, ekey.c_str());
        break;
    default: //调试用，防止写错了没发现
        cout << "read(错了)" << endl;
        pause();
        break;
    }
    f.close();
    return 1;
}

void student::write(int choice)
{
    student w;
    fstream f("data\\student.dat", ios::in | ios::out | ios::binary);
    f.seekp(0, ios::beg);
    do
    {
        f.read((char *)&w, sizeof(student));
    } while (strcmp(phone_number, w.phone_number) && !endmark(w));
    switch (choice)
    {
    case 0: //注册
        f.seekp(-long(sizeof(student)), ios::cur);
        set_name();
        set_password();
        //用base64简单加密了一下
        strcpy_s(w.password, base64_encode(password).c_str());
        strcpy_s(w.phone_number, base64_encode(phone_number).c_str());
        strcpy_s(w.name, base64_encode(name).c_str());
        f.write((char *)&w, sizeof(student));
        f.write((char *)&mark, sizeof(student));
        cout << "\n[INFO]注册成功\n" << endl;
        break;
    case 1: //写个人基本信息
        strcpy_s(w.province, base64_encode(province).c_str());
        strcpy_s(w.nation, base64_encode(nation).c_str());
        strcpy_s(w.political_status, base64_encode(political_status).c_str());
        strcpy_s(w.school_name, base64_encode(school_name).c_str());
        strcpy_s(w.student_number, base64_encode(student_number).c_str());
        strcpy_s(w.id, base64_encode(id).c_str());
        strcpy_s(w.gender, base64_encode(gender).c_str());
        strcpy_s(w.email, base64_encode(email).c_str());
        //置写指针位置，设置错误会覆盖信息
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    case 2: //写家长信息
        strcpy_s(w.dad_name, base64_encode(dad_name).c_str());
        strcpy_s(w.dad_phone_number, base64_encode(dad_phone_number).c_str());
        strcpy_s(w.mom_name, base64_encode(mom_name).c_str());
        strcpy_s(w.mom_phone_number, base64_encode(mom_phone_number).c_str());
        strcpy_s(w.dad_work_address, base64_encode(dad_work_address).c_str());
        strcpy_s(w.mom_work_address, base64_encode(mom_work_address).c_str());
        strcpy_s(w.dad_job, base64_encode(dad_job).c_str());
        strcpy_s(w.mom_job, base64_encode(mom_job).c_str());
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    case 3: //写个人经历
        for (int i = 0; i < 6; i++)
            strcpy_s(w.experience[i], base64_encode(experience[i]).c_str());
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    case 4: //写成绩
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 13; j++)
                w.score[i][j] = score[i][j];
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    case 5: //写密码
        strcpy_s(w.password, base64_encode(password).c_str());
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    case 8: //写空白信息
    {
        student empty;
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&empty, sizeof(student));
        break;
    }
    case 9: //写密保
        strcpy_s(w.security_question, base64_encode(security_question).c_str());
        strcpy_s(w.security_answer, base64_encode(security_answer).c_str());
        f.seekp(-long(sizeof(student)), ios::cur);
        f.write((char *)&w, sizeof(student));
        break;
    }
    f.close();
}

void student::print_is_approved()
{
    const char *p[] = {"未审批", "已过审", "未过审"};
    cout << p[is_approved] << endl;
}

bool student::confirm_password()
{
    string pass1, pass2;
    cout << "\n[INFO]请输入密码！输入0返回\n"
         << endl;
    while (cin >> pass1)
    {
        if (pass1 == "0")
        {
            cout << "\n[INFO]已取消\n"
                 << endl;
            cls();
            return 0;
        }
        string s = base64_decode(password);
        if (pass1 == s)
        {
            cout << "\n[INFO]请再次输入密码确认！输入0返回\n"
                 << endl;
            cin >> pass2;
            if (pass2 == "0")
            {
                cout << "\n[INFO]已取消\n"
                     << endl;
                cls();
                return 0;
            }
            if (pass1 == pass2)
                return 1;
        }
        else
            cerr << "\n[WRONG]密码错误！请重新输入！输入0返回\n"
                 << endl;
    }
    return 0;
}

bool student::change_password()
{
    cls();
    if (confirm_password())
    {
        while (1)
        {
            cout << "\n请输入新密码：" << endl;
            string pass;
            cin >> pass;
            if (password_check(pass))
            {
                strcpy_s(password, pass.c_str());
                cout << "\n密码修改成功！请重新登录！" << endl;
                write(5);
                return 1;
            }
        }
    }
    return 0;
}

bool student::cancel_account()
{
    cout << "\n[INFO]确定要注销账号吗？"
         << "\n\n1.确定；其他.取消" << endl;
    string choice;
    cin >> choice;
    if (choice == "1")
    {
        if (confirm_password())
        {
            cout << "\n注销账号成功" << endl;
            write(8);
            pause();
            return 1;
        }
    }
    cout << "\n已取消" << endl;
    pause();
    cls();
    cin.sync();
    return 0;
}

//重载 = 来读取个人信息 sort会调用=，而如果=进行了base64加解密之类的操作，会导致反复解码最终乱码
//所以不能重载=进行额外操作,不要改变=原本的意义，要重载也只是单纯复制不要搞别的操作
void student::cpy_info(const student &r)
{
    //登录后读取用户个人信息
    strcpy_s(password, r.password); //不解码提高安全性
    strcpy_s(id, base64_decode(r.id).c_str());
    strcpy_s(phone_number, r.phone_number);
    strcpy_s(gender, base64_decode(r.gender).c_str());
    strcpy_s(student_number, base64_decode(r.student_number).c_str());
    strcpy_s(name, base64_decode(r.name).c_str());
    strcpy_s(province, base64_decode(r.province).c_str());
    strcpy_s(nation, base64_decode(r.nation).c_str());
    strcpy_s(political_status, base64_decode(r.political_status).c_str());
    strcpy_s(school_name, base64_decode(r.school_name).c_str());
    strcpy_s(security_question, base64_decode(r.security_question).c_str());
    strcpy_s(security_answer, base64_decode(r.security_answer).c_str());
    strcpy_s(email, base64_decode(r.email).c_str());
    is_approved = r.is_approved;
    //读取家长信息
    strcpy_s(dad_name, base64_decode(r.dad_name).c_str());
    strcpy_s(dad_phone_number, base64_decode(r.dad_phone_number).c_str());
    strcpy_s(dad_job, base64_decode(r.dad_job).c_str());
    strcpy_s(dad_work_address, base64_decode(r.dad_work_address).c_str());
    strcpy_s(mom_name, base64_decode(r.mom_name).c_str());
    strcpy_s(mom_phone_number, base64_decode(r.mom_phone_number).c_str());
    strcpy_s(mom_job, base64_decode(r.mom_job).c_str());
    strcpy_s(mom_work_address, base64_decode(r.mom_work_address).c_str());
    //读取个人经历
    for (int i = 0; i < 6; i++)
        strcpy_s(experience[i], base64_decode(r.experience[i]).c_str());
    //读取成绩
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 13; j++)
            score[i][j] = r.score[i][j];
    }
    overall_score=r.overall_score;
}