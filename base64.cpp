#include "base64.h"

//https://zhuanlan.zhihu.com/p/103336186
//https://github.com/ReneNyffenegger/cpp-base64

string base64_encode(const string &bytes_to_encode)
{
    string ret;
    int i = 0, j = 0,str=0,in_len=bytes_to_encode.length();
    unsigned char char_array_3[3]; // 将三个字符储存为3*8=24个bit
    unsigned char char_array_4[4]; // 将三个字符储存为4*6=24个bit（重新分成4组）
    while (in_len--)
    {
        char_array_3[i++] = bytes_to_encode[str++]; // 存入字符
        if (i == 3)
        {
            //&是为了消高位
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;                                     // 存入第一组的前6个bit
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4); // 存入第一组后2个bit和第二组的前4个bit
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6); // 存入第二组后4个bit和第三组的前2个bit
            char_array_4[3] = char_array_3[2] & 0x3f;                                            // 存入第三组的后6个bit
            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))       //如果最后一组不足3个字符，则补充'='以确保能构成4*6=24个bit的组
            ret += '=';
    }

    return ret;
}

string base64_decode(const char encoded_string[])
{
    size_t in_len = strlen(encoded_string);
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i)
    {
        for (j = 0; j < i; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        for (j = 0; (j < i - 1); j++)
            ret += char_array_3[j];
    }

    return ret;
}
