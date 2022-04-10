#include "admin.h"

void admin::signup()
{
    set_name();
    set_id();
    set_password();
    set_phone_number();
    authority = 1;
}