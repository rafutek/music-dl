#ifndef TAGGER
#define TAGGER

#include "variables.hpp"
#include "format.hpp"
#include <string>
#include <taglib/fileref.h>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

class Tagger
{
private:
    Variables *vars;
    TagLib::FileRef file;
    
public:
    Tagger();
    Tagger(Variables *vars);
    ~Tagger();
    void tag(const path &filepath);
    void setCoverTag(const path &filepath);
    TagLib::FileRef getTaggedFile();
};

#endif