#include "variables.hpp"
#include <iostream>
using namespace std;

/**
 * Constructor used to initialize the variables.
 */
Variables::Variables()
{
    prog_name = "";
    description = "";
    url = "";
    language = Lang::EN;
    cover_path = "";
    extract_cover = false;
    artist = "";
    extract_artist = false;
    album = "";
    genre = "";
    year = 0;
    dest_dir = ".";
    expressions = {};
    format = Format::MP3;
    track_number = 0;
    title = "";
}
Variables::~Variables() {}

/**
 * Print all the variables.
 */
void Variables::printAll()
{
    cout << "Current variables are...\n"
         << "url: " << getURL() << "\n"
         << "language: " << getLanguage().getLang() << "\n"
         << "cover path: " << getCoverPath() << "\n"
         << "extract cover: " << extractCover() << "\n"
         << "artist: " << getArtist() << "\n"
         << "extract artist: " << extractArtist() << "\n"
         << "album: " << getAlbum() << "\n"
         << "genre: " << getGenre() << "\n"
         << "year: " << getYear() << "\n"
         << "track number: " << getTrackNumber() << "\n"
         << "title: " << getTitle() << "\n"
         << "destination directory: " << getDestDir() << "\n"
         << "format: " << getFormat() << "\n"
         << "remove expressions: ";
    for (auto &&e : getExpressions())
    {
        cout << e << " ";
    }
    cout << "\n\n";
}

/**
 * These are the setters and getters of the variables.
 * Note that getters are const member function, so the object can't be modified.
 */

void Variables::setProgName(const string &prog_name) { this->prog_name = prog_name; }
const string Variables::getProgName() const { return prog_name; }

void Variables::setDescription(const string &description) { this->description = description; }
const string Variables::getDescription() const { return description; }

void Variables::setURL(const string &url) { this->url = url; }
const string Variables::getURL() const { return this->url; }

void Variables::setLanguage(const Lang &lang) { language = Language(lang); }
const Language Variables::getLanguage() const { return language; }

void Variables::setCoverPath(const string &cover_path) { this->cover_path = cover_path; }
const string Variables::getCoverPath() const { return cover_path; }

void Variables::setExtractCover(const bool &extract_cover)
{
    this->extract_cover = extract_cover;
}
const bool Variables::extractCover() const { return extract_cover; }

void Variables::setExtractArtist(const bool &extract_artist)
{
    this->extract_artist = extract_artist;
}
const bool Variables::extractArtist() const { return extract_artist; }

void Variables::setArtist(const string &artist) { this->artist = artist; }
const string Variables::getArtist() const { return artist; }

void Variables::setAlbum(const string &album) { this->album = album; }
const string Variables::getAlbum() const { return album; }

void Variables::setGenre(const string &genre) { this->genre = genre; }
const string Variables::getGenre() const { return genre; }

void Variables::setYear(const unsigned int &year) { this->year = year; }
const unsigned int Variables::getYear() const { return year; }

void Variables::setDestDir(const string &dest_dir) { this->dest_dir = dest_dir; }
const string Variables::getDestDir() const { return dest_dir; }

void Variables::setExpressions(const vector<string> &expressions)
{
    this->expressions = expressions;
}
const vector<string> Variables::getExpressions() const { return this->expressions; }

void Variables::setFormat(const Format &format) { this->format = format; }
const Format Variables::getFormat() const { return format; }

void Variables::setTrackNumber(const unsigned int &track_number)
{
    this->track_number = track_number;
}
const unsigned int Variables::getTrackNumber() const { return track_number; }

void Variables::setTitle(const string &title) { this->title = title; }
const string Variables::getTitle() const { return title; }

/**
 * Return true if the variables set are compatible.
 */
bool Variables::areCompatible()
{
    bool compatible = true;
    if (!cover_path.empty() && extract_cover)
    {
        compatible = false;
    }
    if (artist != language.unknown() && extract_artist)
    {
        compatible = false;
    }
    return compatible;
}