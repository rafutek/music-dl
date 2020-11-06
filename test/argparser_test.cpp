#include <boost/test/unit_test.hpp>
#include "../src/argparser.hpp"
using namespace std;


BOOST_AUTO_TEST_SUITE(ArgparserTestSuite)

const char *progname = "music-dl";
const char *url = "http://music-adress";
Language language(Lang::FR);

////////////////////////////////////////////////////////
// Basic settings tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(prog_url_variables)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the program name and url variables must be the same
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getProgName() == progname);
    BOOST_TEST(vars->getURL() == url);
}

////////////////////////////////////////////////////////
// Language setting tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(language_locale)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the language must be locale
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getLanguage().getLang() == Lang::FR);
}

BOOST_AUTO_TEST_CASE(language_opt_fr)
{
    // Given a command with fr language option
    const char *argv[] = {progname, "-l", "fr", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the language must be fr
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getLanguage().getLang() == Lang::FR);
    BOOST_TEST(vars->getLanguage().unknown() == "Inconnu");
}

BOOST_AUTO_TEST_CASE(language_opt_en)
{
    // Given a command with 'en' language option
    const char *argv[] = {progname, "-l", "en", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the language must be 'EN'
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getLanguage().getLang() == Lang::EN);
    BOOST_TEST(vars->getLanguage().unknown() == "Unknown");
}

////////////////////////////////////////////////////////
// Cover settings tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_cover_opt)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then extract and cover path variables are false and empty
    Variables *vars = argparser.getVariables();
    BOOST_TEST(!vars->extractCover());
    BOOST_TEST(vars->getCoverPath().empty());
}

BOOST_AUTO_TEST_CASE(extract_cover_opt)
{
    // Given a command with extract cover option
    const char *argv[] = {progname, "--extract-cover", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then extract and cover path variables are true and empty
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->extractCover());
    BOOST_TEST(vars->getCoverPath().empty());
}

BOOST_AUTO_TEST_CASE(cover_path_opt)
{
    // Given a command with cover path option
    const char *coverpath = "./test.jpg";
    const char *argv[] = {progname, "-c", coverpath, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then extract cover is false and cover path is the same
    Variables *vars = argparser.getVariables();
    BOOST_TEST(!vars->extractCover());
    BOOST_TEST(vars->getCoverPath() == coverpath);
}

////////////////////////////////////////////////////////
// Tag settings tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_tag_opts)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then those tags must have these default values
    Variables *vars = argparser.getVariables();
    BOOST_TEST(!vars->extractArtist());
    BOOST_TEST(vars->getArtist() == language.unknown());
    BOOST_TEST(vars->getAlbum() == language.unknown());
    BOOST_TEST(vars->getGenre() == language.unknown());
    BOOST_TEST(vars->getYear() == 0);
}

BOOST_AUTO_TEST_CASE(extract_artist_opt)
{
    // Given a command with extract artist option
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then extract artist variable must be true
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->extractArtist());
}

BOOST_AUTO_TEST_CASE(full_tag_opts)
{
    // Given a command with all possible tag options
    const char *artist = "Ray Blue";
    const char *album = "Work";
    const char *genre = "Jazz";
    const char *year = "2019";
    const char *argv[] = {progname, "-a", artist, "-A", album, "-g", genre, "-y", year, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then those tags must have the given values
    Variables *vars = argparser.getVariables();
    BOOST_TEST(!vars->extractArtist());
    BOOST_TEST(vars->getArtist() == artist);
    BOOST_TEST(vars->getAlbum() == album);
    BOOST_TEST(vars->getGenre() == genre);
    BOOST_TEST(vars->getYear() == 2019);
}

////////////////////////////////////////////////////////
// Destination directory setting tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_dir_opt)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then destination directory must be the current one
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getDestDir() == ".");
}

BOOST_AUTO_TEST_CASE(dir_opt)
{
    // Given a command with a valid destination directory option
    const char *dest_dir = "./dest";
    const char *argv[] = {progname, "-d", dest_dir, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then destination directory must be the given one
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getDestDir() == dest_dir);
}

////////////////////////////////////////////////////////
// Remove expressions setting tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_remove_ex_opt)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the remove expressions variable must be empty
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getExpressions().empty());
}

BOOST_AUTO_TEST_CASE(remove_ex_opt)
{
    // Given a command with expressions to remove
    vector<string> exps = {"(Official)", "Live"};
    const char *argv[] = {progname, "-r", exps[0].c_str(), "-r", exps[1].c_str(), url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the remove expressions variable must contain all given ones
    Variables *vars = argparser.getVariables();
    vector<string> var_exps = vars->getExpressions();
    BOOST_TEST(var_exps.size() == exps.size());
    for (size_t i = 0; i < var_exps.size(); i++)
    {
        BOOST_TEST(var_exps[i] == exps[i]);
    }
}

////////////////////////////////////////////////////////
// Audio format setting tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_format_opt)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the format variable must be MP3
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getFormat() == Format::MP3);
}

BOOST_AUTO_TEST_CASE(format_mp3_opt)
{
    // Given a command with mp3 format option
    const char *argv[] = {progname, "-f", "mp3", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command
    ArgParser argparser(argc, argv);

    // Then the format variable must be MP3
    Variables *vars = argparser.getVariables();
    BOOST_TEST(vars->getFormat() == Format::MP3);
}

BOOST_AUTO_TEST_SUITE_END()
