#ifndef USER_H
#define USER_H

#include <string>
#include <cstring>
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
    void set_password();
    void set_name();
    void set_province();
    std::string set_college();
    std::string set_phone_number();
    std::string get_phone();
    std::string get_name();
    std::string get_id();
    std::string get_province();
    template <typename T>
    bool endmark(T &s)
    {
        return strcmp((s.get_phone()).c_str(), "nophone") == 0;
    }
};

#endif