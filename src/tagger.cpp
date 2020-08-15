#include "tagger.hpp"
#include "format.hpp"
#include <iostream>
#include <taglib/tag.h>

using namespace std;

Tagger::Tagger() {}

Tagger::Tagger(Variables *vars)
{
    this->vars = vars;
}

Tagger::~Tagger() {}

TagLib::FileRef Tagger::getTaggedFile()
{
    return file;
}

void Tagger::tag(const path &filepath)
{
    file = TagLib::FileRef(filepath.c_str());
    file.tag()->setArtist(vars->getArtist());
    file.tag()->setAlbum(vars->getAlbum());
    file.tag()->setGenre(vars->getGenre());
    if (vars->getYear() > 0)
        file.tag()->setYear(vars->getYear());
    if (vars->getTrackNumber() > 0)
        file.tag()->setTrack(vars->getTrackNumber());
    file.tag()->setTitle(vars->getTitle());
    file.save();
}
