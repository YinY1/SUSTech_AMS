#ifndef BASE64_H
#define BASE64_H
#include <string>
#include <cstring>

//base64编码表
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const std::string &bytes_to_encode);
std::string base64_decode(const char encoded_string[]);

#endif