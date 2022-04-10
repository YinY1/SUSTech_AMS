#ifndef BASE64_H
#define BASE64_H
#include <string>
#include <cstring>
using namespace std;  

//base64编码表
static const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_encode(const string &bytes_to_encode);
string base64_decode(const char encoded_string[]);

#endif