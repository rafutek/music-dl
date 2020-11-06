#include "argparser.hpp"
#include "variables.hpp"
#include "format.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

/**
 * Constructor used to parse the command and set the variables.
 * @param argc Number of elements in argv.
 * @param argv Array of strings containing options and values.
 */
ArgParser::ArgParser(int argc, const char *argv[])
{
    const string prog_name = argv[0];
    const string usage = "Usage: " + prog_name + " [OPTIONS] URL";
    const string description =
        "\n" + prog_name + " is a program for GNU/Linux users to download and tag music." +
        "\n\n" + usage + "\n";
    const string opt_help = "help", full_opt_help = opt_help + ",h";
    const string opt_url = "url", full_opt_url = opt_url + ",u";
    const string opt_lang = "lang", full_opt_lang = opt_lang + ",l";
    const string opt_cover_path = "cover-path", full_opt_cover_path = opt_cover_path + ",c";
    const string opt_x_cover = "extract-cover";
    const string opt_x_artist = "extract-artist";
    const string opt_artist = "artist", full_opt_artist = opt_artist + ",a";
    const string opt_album = "album", full_opt_album = opt_album + ",A";
    const string opt_genre = "genre", full_opt_genre = opt_genre + ",g";
    const string opt_year = "year", full_opt_year = opt_year + ",y";
    const string opt_dest_dir = "dest-dir", full_opt_dest_dir = opt_dest_dir + ",d";
    const string opt_rm_exp = "remove-ex", full_opt_rm_exp = opt_rm_exp + ",r";
    const string opt_format = "format", full_opt_format = opt_format + ",f";

    po::options_description all_desc("All");
    po::options_description opt_desc("Options");
    po::options_description required_desc("Required");
    po::positional_options_description pos_opt_desc;
    try
    {
        po::options_description_easy_init required_desc_adder = required_desc.add_options();
        required_desc_adder(full_opt_url.c_str(), po::value<string>(),
                            "set the url of the music to download and tag");
        pos_opt_desc.add(opt_url.c_str(), 1);

        po::options_description_easy_init opt_desc_adder = opt_desc.add_options();
        opt_desc_adder(full_opt_help.c_str(), "Print this help message");
        opt_desc_adder(full_opt_lang.c_str(),
                       po::value<string>(), "Set language for unknown tags \n"
                                            "choices: ['en', 'fr'] "
                                            "(locale or 'en' by default)");
        opt_desc_adder(full_opt_cover_path.c_str(),
                       po::value<string>(), "Set cover from local image");
        opt_desc_adder(opt_x_cover.c_str(), "Extract the cover from the website");
        opt_desc_adder(full_opt_artist.c_str(), po::value<string>(), "Set artist name tag");
        opt_desc_adder(opt_x_artist.c_str(), "Extract artist name from music titles");
        opt_desc_adder(full_opt_album.c_str(), po::value<string>(), "Set album name tag");
        opt_desc_adder(full_opt_genre.c_str(), po::value<string>(), "Set album genre tag");
        opt_desc_adder(full_opt_year.c_str(), po::value<string>(), "Set album year tag");
        opt_desc_adder(full_opt_dest_dir.c_str(), po::value<string>(), "Set destination directory");
        opt_desc_adder(full_opt_rm_exp.c_str(), po::value<vector<string>>(),
                       "Remove expression from titles\n"
                       "(option can be used multiple times)");
        opt_desc_adder(full_opt_format.c_str(), po::value<string>(),
                       "Set audio format\n"
                       "choices: ['mp3'] ('mp3' by default)");

        all_desc.add(opt_desc).add(required_desc);

        po::parsed_options parsed_opt = po::command_line_parser(argc, argv)
                                            .options(all_desc)
                                            .positional(pos_opt_desc)
                                            .run();
        po::store(parsed_opt, var_map);
        po::notify(var_map);
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
        exit(1);
    }

    vars.setProgName(prog_name);
    vars.setDescription(description);
    checkHelp(opt_help, argc, opt_desc);
    checkAndSetURL(opt_url);
    checkAndSetLang(opt_lang);
    checkAndSetCoverPath(opt_cover_path);
    checkAndSetExtractCover(opt_x_cover);
    checkAndSetExtractArtist(opt_x_artist);
    checkAndSetArtist(opt_artist);
    checkAndSetAlbum(opt_album);
    checkAndSetGenre(opt_genre);
    checkAndSetYear(opt_year);
    checkAndSetDestDir(opt_dest_dir);
    checkAndSetExpressions(opt_rm_exp);
    checkAndSetFormat(opt_format);
}

ArgParser::~ArgParser() {}

Variables *ArgParser::getVariables()
{
    return &vars;
}

/**
 * Returns the value of the given option.
 * @param opt_name Name of the option.
 */
string ArgParser::getOptionValue(string opt_name)
{
    string value;
    if (var_map.count(opt_name))
    {
        value = var_map[opt_name].as<string>();
    }
    return value;
}

/**
 * Returns the multiple values of the given option.
 * @param opt_name Name of the option.
 */
vector<string> ArgParser::getOptionValues(string opt_name)
{
    vector<string> values;
    if (var_map.count(opt_name))
    {
        values = var_map[opt_name].as<vector<string>>();
    }
    return values;
}

/**
 * Returns the value of the given option, 
 * or the default value if not found.
 * @param opt_name Name of the option.
 */
string ArgParser::getOptionValue(string opt_name, string default_value)
{
    string value = getOptionValue(opt_name);
    if (value.empty())
    {
        value = default_value;
    }
    return value;
}

/**
 * Prints the help message and exits if the command line
 * had the help option or no argument.
 * @param opt_help Name of help option.
 * @param argc Number of command line arguments.
 * @param opt_desc Description of the program options.
 */
void ArgParser::checkHelp(const string opt_help, const int argc, po::options_description opt_desc)
{
    if (argc == 1 || var_map.count(opt_help))
    {
        cout << vars.getDescription() << "\n"
             << opt_desc << '\n';
        exit(0);
    }
}

/**
 * Sets the url variable depending on its option name, 
 * or quit if not found in the options.
 * @param opt_url Name of the url option.
 */
void ArgParser::checkAndSetURL(const string opt_url)
{
    string url = getOptionValue(opt_url);
    if (!url.empty())
    {
        vars.setURL(url);
    }
    else
    {
        cerr << "url is required\n";
        exit(1);
    }
}

/**
 * Sets the language variable depending on its option name.
 * If not found, sets language from locale. 
 * Quit if option value (or locale) is not supported.
 * @param  opt_lang  Name of language option.
*/
void ArgParser::checkAndSetLang(const string opt_lang)
{
    string lang = getOptionValue(opt_lang);
    if (lang.empty())
    {
        setlocale(LC_ALL, "");
        string locale_lang = setlocale(LC_ALL, NULL);
        lang = locale_lang.substr(0, 2);
    }

    if (lang == "en")
        vars.setLanguage(Lang::EN);
    else if (lang == "fr")
        vars.setLanguage(Lang::FR);
    else
    {
        cerr << "language " << lang << " is not handled\n";
        exit(1);
    }
}

/**
 * Returns true if the given parameter is a regular file
 * with an image extension (jpg, jpeg or png).
 * @param filepath Path to the image file.
 */
bool ArgParser::isImage(const string filepath)
{
    if (fs::is_regular_file(filepath))
    {
        const vector<string> img_exts{".jpg", ".jpeg", ".png"};
        const string file_ext = fs::extension(filepath);
        for (string img_ext : img_exts)
        {
            if (img_ext == file_ext)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Sets the cover path variable depending on given option name.
 * If the option name is found in the parsed options it will
 * check that the file exists before setting it. Exit with error
 * if file was not found.
 * @param opt_cover_path Name of cover path option.
 */
void ArgParser::checkAndSetCoverPath(const string opt_cover_path)
{
    string cover_path = getOptionValue(opt_cover_path);
    if (!cover_path.empty())
    {
        if (isImage(cover_path))
        {
            vars.setCoverPath(cover_path);
        }
        else
        {
            cerr << "cover file '" << cover_path << "' is not an image or does not exist\n";
            exit(1);
        }
    }
}

/**
 * Sets the extract cover variable to true if the given option name
 * is in the parsed options. False otherwise.
 * @param opt_x_cover Name of extract cover option.
 */
void ArgParser::checkAndSetExtractCover(const string opt_x_cover)
{
    bool extract_cover = var_map.count(opt_x_cover);
    vars.setExtractCover(extract_cover);
}

/**
 * Sets the extract artist variable to true if the given option name
 * is in the parsed options. False otherwise.
 * @param opt_x_artist Name of extract artist option.
 */
void ArgParser::checkAndSetExtractArtist(const string opt_x_artist)
{
    bool extract_artist = var_map.count(opt_x_artist);
    vars.setExtractArtist(extract_artist);
}

/**
 * Sets artist variable depending on its option name. 
 * Set to unknown if option is not found, 
 * unknown value depending on language.
 * @param opt_artist Name of the artist option.
 */
void ArgParser::checkAndSetArtist(const string opt_artist)
{
    string default_val = this->vars.getLanguage().unknown();
    string artist = getOptionValue(opt_artist, default_val);
    vars.setArtist(artist);
}

/**
 * Sets album variable depending on its option name. 
 * Set to unknown if option is not found, 
 * unknown value depending on language.
 * @param opt_album Name of the album option.
 */
void ArgParser::checkAndSetAlbum(const string opt_album)
{
    string default_val = this->vars.getLanguage().unknown();
    string album = getOptionValue(opt_album, default_val);
    vars.setAlbum(album);
}

/**
 * Sets genre variable depending on its option name. 
 * Set to unknown if option is not found, 
 * unknown value depending on language.
 * @param opt_genre Name of the genre option.
 */
void ArgParser::checkAndSetGenre(const string opt_genre)
{
    string default_val = this->vars.getLanguage().unknown();
    string genre = getOptionValue(opt_genre, default_val);
    vars.setGenre(genre);
}

/**
 * Sets year variable depending on its option name. 
 * Quit if value is not a number. 
 * Set to 0 if option is not found.
 * @param opt_year Name of the year option.
 */
void ArgParser::checkAndSetYear(const string opt_year)
{
    string year = getOptionValue(opt_year);
    if (isNumber(year))
    {
        vars.setYear(stoi(year));
    }
    else if (!year.empty())
    {
        cerr << "year must be a number\n";
        exit(1);
    }
    else
        vars.setYear(0);
}

/**
 * Sets destination directory variable depending on its option name. 
 * Quit if given directory is not found on the system.
 * Set to current directory if option is not found.
 * @param opt_dest_dir Name of the destination directory option.
 */
void ArgParser::checkAndSetDestDir(const string opt_dest_dir)
{
    string dest_dir = getOptionValue(opt_dest_dir);
    if (!dest_dir.empty())
    {
        if (fs::is_directory(dest_dir))
        {
            vars.setDestDir(dest_dir);
        }
        else
        {
            cerr << "destination directory '" << dest_dir
                 << "' is not a directory or does not exist\n";
            exit(1);
        }
    }
    else
        vars.setDestDir(".");
}

/**
 * Sets expressions to remove variable depending on its option name.
 * @param opt_exp Name of the expressions to remove option.
 */
void ArgParser::checkAndSetExpressions(const string opt_exp)
{
    vector<string> expressions = getOptionValues(opt_exp);
    if (!expressions.empty())
    {
        vars.setExpressions(expressions);
    }
}

/**
 * Sets audio format variable depending on its option name. 
 * Set to mp3 if option is not found.
 * Quit if the given format is not supported.
 * @param opt_format Name of the audio format option.
 */
void ArgParser::checkAndSetFormat(const string opt_format)
{
    string str_format = getOptionValue(opt_format);
    Format format;
    if (str_format.empty())
    {
        format = Format::MP3; // default value
    }
    else
        format = stringToFormat(str_format);

    if (isValidFormat(format))
    {
        vars.setFormat(format);
    }
    else
    {
        cerr << "format " << str_format << " is not supported\n";
        exit(1);
    }
}