#ifndef LANGUAGE
#define LANGUAGE

#include <string>
using namespace std;

enum Lang
{
    EN,
    FR
};

class Language
{
private:
    Lang lang;

public:
    Language();
    Language(const Lang &lang);
    const Lang getLang() const;
    const string unknown() const;
};

#endif