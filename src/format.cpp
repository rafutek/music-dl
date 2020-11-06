#include "format.hpp"
#include <iostream>
using namespace std;

string formatToString(const Format &format) {
    string str;
    switch (format) {
    case Format::MP3:
        str = "mp3";
        break;
    }
    return str;
}

Format stringToFormat(const string &str) {
    Format format;
    if (str == "mp3") {
        format = Format::MP3;
    }
    return format;
}

bool isValidFormat(const Format &format) {
    switch (format)
    {
    case Format::MP3:
        return true;
    default:
        return false;
    }
}