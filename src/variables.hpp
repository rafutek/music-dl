#ifndef VARIABLES
#define VARIABLES

#include "language.hpp"
#include "format.hpp"
#include <string>
#include <vector>
using namespace std;

/**
 * Store important variables used by different classes.
 */
class Variables
{
private:
    string prog_name;
    string description;
    string url;
    Language language;
    string cover_path;
    bool extract_cover;
    string artist;
    bool extract_artist;
    string album;
    string genre;
    unsigned int year;
    string dest_dir;
    vector<string> expressions;
    Format format;
    unsigned int track_number;
    string title;

public:
    Variables();
    ~Variables();
    void setProgName(const string &prog_name);
    const string getProgName() const;
    void setDescription(const string &description);
    const string getDescription() const;
    void setLanguage(const Lang &lang);
    const Language getLanguage() const;
    void setCoverPath(const string &cover_path);
    const string getCoverPath() const;
    void setExtractCover(const bool &extract_cover);
    const bool extractCover() const;
    void setExtractArtist(const bool &extract_artist);
    const bool extractArtist() const;
    void setURL(const string &url);
    const string getURL() const;
    void setArtist(const string &artist);
    const string getArtist() const;
    void setAlbum(const string &album);
    const string getAlbum() const;
    void setGenre(const string &genre);
    const string getGenre() const;
    void setYear(const unsigned int &year);
    const unsigned int getYear() const;
    void setDestDir(const string &dest_dir);
    const string getDestDir() const;
    void setExpressions(const vector<string> &expressions);
    const vector<string> getExpressions() const;
    void setFormat(const Format &format);
    const Format getFormat() const;
    void setTrackNumber(const unsigned int &track_number);
    const unsigned int getTrackNumber() const;
    void setTitle(const string &title);
    const string getTitle() const;
    bool areCompatible();
    void printAll();
};

#endif