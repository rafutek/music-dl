#include <boost/test/unit_test.hpp>
#include "../src/argparser.hpp"
#include "../src/extractor.hpp"
#include <regex>
using namespace std;

BOOST_AUTO_TEST_SUITE(ExtractorTestSuite)

const char *progname = "music-dl";
const char *url = "http://test-music-adress";
const string dl_dir = "dl";
Language language(Lang::FR);

BOOST_AUTO_TEST_CASE(set_file)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());

    // When setting the file
    const string stem = "great artist - great song";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // Then the filename must be this one
    BOOST_TEST(extractor.getFile().filename().string() == filename);
}

////////////////////////////////////////////////////////
// Basic extraction tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_spaces_around)
{
    // Given the basic command and a file stem without spaces around
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = "great artist - great song";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the title must equal the file stem
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getTitle() == stem);
}

BOOST_AUTO_TEST_CASE(spaces_around)
{
    // Given the basic command and a file stem with spaces around
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem_wo_spaces = "great artist - great song";
    const string stem = " " + stem_wo_spaces + " ";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the title must equal the stem without spaces
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getTitle() == stem_wo_spaces);
}

////////////////////////////////////////////////////////
// Extract artist tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_artist)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = "great artist - great song";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the artist must still be unknown and title must equal stem
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getArtist() == language.unknown());
    BOOST_TEST(vars->getTitle() == stem);
}

BOOST_AUTO_TEST_CASE(extract_artist)
{
    // Given the basic command
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = " great artist - great song ";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the artist and title must have these values
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getArtist() == "great artist");
    BOOST_TEST(vars->getTitle() == "great song");
}

BOOST_AUTO_TEST_CASE(extract_artist_but_no_artist)
{
    // Given the basic command
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = " great song ";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the artist must still be unknown and title must have this value
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getArtist() == language.unknown());
    BOOST_TEST(vars->getTitle() == "great song");
}

BOOST_AUTO_TEST_CASE(extract_artist_but_multiple_dashes)
{
    // Given the basic command
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = " great artist - great song - with - dashes ";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the artist and title must have these values
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getArtist() == "great artist");
    BOOST_TEST(vars->getTitle() == "great song - with - dashes");
}

////////////////////////////////////////////////////////
// Extract track number tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(no_track_number)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = "great artist - great song";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the track number must be 0 and title unchanged
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getTrackNumber() == 0);
    BOOST_TEST(vars->getTitle() == stem);
}

BOOST_AUTO_TEST_CASE(extract_track_number)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string track_field = "17_";
    const string stem = "great artist - great song";
    const string stem_w_track = track_field + stem;
    const string filename = stem_w_track + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the track number must be 17 and removed from title
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getTrackNumber() == 17);
    BOOST_TEST(vars->getTitle() == stem);
}

BOOST_AUTO_TEST_CASE(extract_track_not_number)
{
    // Given the basic command
    // and a filename with track field not containing a number
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string track_field = "NAN_";
    const string stem = "great artist - great song";
    const string stem_w_track = track_field + stem;
    const string filename = stem_w_track + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the track number must be 0 and track field removed from title
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getTrackNumber() == 0);
    BOOST_TEST(vars->getTitle() == stem);
}

////////////////////////////////////////////////////////
// Remove expressions tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(remove_expressions)
{
    // Given a command with expressions to remove
    vector<string> exps = {"(live)", "great "};
    const char *argv[] = {progname, "-r", exps[0].c_str(), "-r", exps[1].c_str(), url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = "great song with great title (live)";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the expressions must be removed
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getTitle() == "song with title");
}

BOOST_AUTO_TEST_CASE(extract_artist_remove_expressions)
{
    // Given a command with expressions to remove
    vector<string> exps = {"(live)", "great "};
    const char *argv[] = {progname, "--extract-artist",
                          "-r", exps[0].c_str(), "-r", exps[1].c_str(), url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    const string stem = "great artist - song with great title (live)";
    const string filename = stem + ".ext";
    extractor.setFile(dl_dir + '/' + filename);

    // When extracting
    extractor.extract();

    // Then the expressions must be removed
    Variables *vars = extractor.getVariables();
    BOOST_TEST(vars->getArtist() == "great artist");
    BOOST_TEST(vars->getTitle() == "song with title");
}

BOOST_AUTO_TEST_SUITE_END()