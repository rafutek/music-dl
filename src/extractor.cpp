#include "extractor.hpp"
#include "utils.hpp"
#include <regex>

Extractor::Extractor() {}

Extractor::Extractor(Variables *vars)
{
    this->vars = vars;
}

Extractor::~Extractor() {}

Variables *Extractor::getVariables()
{
    return vars;
}

void Extractor::setFile(const path &filepath)
{
    this->filepath = filepath;
    this->new_stem = filepath.stem().string(); // filename without extension
}

const path Extractor::getFile() const
{
    return this->filepath;
}

void Extractor::extract()
{
    extractTrackNumber();
    if (vars->extractArtist())
    {
        extractArtist();
    }
    if (!vars->getExpressions().empty())
    {
        removeExpressions();
    }
    extractTitle();
}

void Extractor::extractTrackNumber()
{
    if (!new_stem.empty())
    {
        regex e("(^.*)_"); // track field regex
        string track = regex_replace(new_stem, e, "$1", regex_constants::format_no_copy);
        if (track.empty() || !isNumber(track))
        {
            vars->setTrackNumber(0); // to skip track number tag
        }
        else
        {
            vars->setTrackNumber(stoi(track));
        }

        new_stem = regex_replace(new_stem, e, "$2"); // remove track field
    }
    else
    {
        cerr << "cannot extract track number from empty stem\n";
        exit(1);
    }
}

void Extractor::extractArtist()
{
    if (!new_stem.empty())
    {
        regex e(" - (.*)");
        string artist = regex_replace(new_stem, e, "$2"); // $2 contain non matching result
        string song = regex_replace(new_stem, e, "$1", regex_constants::format_no_copy);
        if (!song.empty())
        {
            new_stem = song;
            vars->setArtist(removeSpacesAround(artist));
        }
    }
    else
    {
        cerr << "cannot extract artist from empty stem\n";
        exit(1);
    }
}

void Extractor::removeExpressions()
{
    if (!new_stem.empty())
    {
        const vector<string> expressions = vars->getExpressions();
        for (auto it = expressions.begin(); it != expressions.end(); it++)
        {
            string exp = *it;
            size_t i;
            do
            { // remove all expression occurences
                i = new_stem.find(exp);
                if (i != string::npos)
                {
                    new_stem = new_stem.erase(i, exp.length());
                }
            } while (i != string::npos);
        }
    }
    else
    {
        cerr << "cannot extract artist from empty stem\n";
        exit(1);
    }
}

void Extractor::extractTitle()
{
    if (!new_stem.empty())
    {
        string title = removeSpacesAround(new_stem);
        if (title.empty())
        {
            cerr << "title couldn't be extracted\n";
            exit(1);
        }
        else
            vars->setTitle(title);
    }
    else
    {
        cerr << "cannot extract artist from empty stem\n";
        exit(1);
    }
}