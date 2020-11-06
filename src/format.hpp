#ifndef FORMAT
#define FORMAT
#include <iostream>
using namespace std;

enum Format {
    MP3,
};

string formatToString(const Format &format);
Format stringToFormat(const string &str);
bool isValidFormat(const Format &format);

#endif