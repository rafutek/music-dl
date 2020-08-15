#ifndef EXTRACTOR
#define EXTRACTOR

#include "variables.hpp"
#include <string>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

class Extractor
{
private:
    Variables *vars;
    path filepath;
    string new_stem;

    void extractTrackNumber();
    void extractArtist();
    void removeExpressions();
    void extractTitle();

public:
    Extractor();
    Extractor(Variables *vars);
    ~Extractor();
    Variables *getVariables();
    void setFile(const path &filepath);
    const path getFile() const;
    void extract();
};


#endif