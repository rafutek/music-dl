#include "utils.hpp"
#include <regex>
#include <iostream>
using namespace std;

bool isNumber(const string &s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

string removeSpacesAround(const string &s) {
    regex e("\\s*(\\S.*\\S)\\s*");
    return regex_replace(s, e, "$1");
}

string removeSpaces(const string &s) {
    regex e("\\s*");
    return regex_replace(s, e, "$2");
}