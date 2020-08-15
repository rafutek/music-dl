#include "tagger.hpp"
#include "format.hpp"
#include <iostream>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/id3v2tag.h>

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
    setCoverTag(filepath);
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

/**
 * Local class used to store the cover file.
 */
class ImageFile : public TagLib::File
{
public:
    ImageFile(const char *file) : TagLib::File(file)
    {
    }

    TagLib::ByteVector data()
    {
        return readBlock(length());
    }

private:
    virtual TagLib::Tag *tag() const { return 0; }
    virtual TagLib::AudioProperties *audioProperties() const { return 0; }
    virtual bool save() { return false; }
};

/**
 * Tags given file with cover if cover path is not empty 
 * and audio format is supported.
 * @param filepath Path of the audio file to add the cover to
 */
void Tagger::setCoverTag(const path &filepath)
{
    if (!vars->getCoverPath().empty())
    {
        ImageFile image_file(vars->getCoverPath().c_str());
        string ext = filepath.extension().string();
        if (ext == ".mp3")
        {
            TagLib::MPEG::File audio_file(filepath.c_str());

            TagLib::ID3v2::Tag *tag = audio_file.ID3v2Tag(true);
            TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame;

            frame->setMimeType("image/jpeg");
            frame->setPicture(image_file.data());

            tag->addFrame(frame);
            audio_file.save();
        }
    }
}