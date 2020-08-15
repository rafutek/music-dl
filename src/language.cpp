#include "language.hpp"

Language::Language()
{
    this->lang = Lang::EN;
}

Language::Language(const Lang &lang)
{
    this->lang = lang;
}

const Lang Language::getLang() const
{
    return this->lang;
}

const string Language::unknown() const
{
    switch (this->lang)
    {
    case Lang::FR:
        return "Inconnu";

    default:
        return "Unknown";
    }
}