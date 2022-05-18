#ifndef USER_H
#define USER_H

#include <cstring>
#include <string>
class user
{
protected:
    char province[10] = {};
    char phone_number[20] = {"nophone"};
    char name[50] = {};
    char id[25] = {};
    char password[20] = {};

public:
    user() {}
    virtual bool login() = 0;
    virtual void show(int) = 0;
    void set_password();
    void set_name();
    void set_province();
    std::string set_college(); //好像没什么用
    std::string set_phone_number()
    {
        std::string phone_number;
    }
    std::string get_phone()
    {
        return phone_number;
    }
    std::string get_name()
    {
        return name;
    }
    std::string get_id()
    {
        return id;
    }
    std::string get_province()
    {
        return province;
    }
    template <typename T>
    bool endmark(T &s)
    {
        return strcmp((s.get_phone()).c_str(), "nophone") == 0;
    }
};

#endif