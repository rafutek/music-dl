#ifndef ARGPARSER
#define ARGPARSER

#include "variables.hpp"
#include <string>
#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;

/**
 * Command line manager. Can parse its arguments, 
 * check their values and set relative variables 
 * used by the rest of the program.
 */
class ArgParser
{
private:
    po::variables_map var_map;
    Variables vars;

    string getOptionValue(string opt_name);
    string getOptionValue(string opt_name, string default_value);
    vector<string> getOptionValues(string opt_name);
    void checkHelp(const string opt_help, const int argc, po::options_description desc);
    void checkAndSetURL(const string opt_url);
    void checkAndSetLang(const string opt_lang);
    bool isImage(const string filepath);
    void checkAndSetCoverPath(const string opt_cover_path);
    void checkAndSetExtractCover(const string opt_x_cover);
    void checkAndSetExtractArtist(const string opt_x_artist);
    void checkAndSetArtist(const string opt_artist);
    void checkAndSetAlbum(const string opt_album);
    void checkAndSetGenre(const string opt_genre);
    void checkAndSetYear(const string opt_year);
    void checkAndSetDestDir(const string opt_dest_dir);
    void checkAndSetExpressions(const string opt_exp);
    void checkAndSetFormat(const string opt_format);

public:
    ArgParser(int argc, const char *argv[]);
    ~ArgParser();
    Variables *getVariables();
};

#endif