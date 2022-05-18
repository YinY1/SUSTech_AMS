#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"

class manager : public user
{
protected:
    char ukey[20] = {};

public:
    bool ukey_check();
    void set_ukey();
    virtual void show(int) = 0;
    std::string get_ukey() { return ukey; }
};

#endif