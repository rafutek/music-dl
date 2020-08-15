#include <boost/test/unit_test.hpp>
#include "../src/argparser.hpp"
#include "../src/tagger.hpp"
#include "../src/extractor.hpp"
#include <taglib/tag.h>
#include <taglib/fileref.h>
using namespace std;
namespace fs = boost::filesystem;

BOOST_AUTO_TEST_SUITE(TaggerTestSuite)

const char *progname = "music-dl";
const char *url = "http://music-adress";
Language language(Lang::FR);
const string dl_tmp = "dl/";
const string filename = "test-audio-file.mp3";
const string filepath = dl_tmp + filename;

////////////////////////////////////////////////////////
// Parse command and tag tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(basic_command_tag)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Tagger tagger(argparser.getVariables());

    // When tagging a file copy
    string new_filepath = dl_tmp + "currently-tested.mp3";
    fs::copy(filepath, new_filepath);
    tagger.tag(new_filepath);

    // Then the file tags must be the default ones
    TagLib::FileRef file = tagger.getTaggedFile();
    BOOST_TEST(file.tag()->artist().toCString() == language.unknown().c_str());
    BOOST_TEST(file.tag()->album().toCString() == language.unknown().c_str());
    BOOST_TEST(file.tag()->genre().toCString() == language.unknown().c_str());
    BOOST_TEST(file.tag()->year() == 0);
    BOOST_TEST(file.tag()->track() == 0);
    fs::remove(file.file()->name());
}

BOOST_AUTO_TEST_CASE(full_tags)
{
    // Given a command with all possible tags
    const char *artist = "Ray Blue";
    const char *album = "Work";
    const char *genre = "Jazz";
    const char *year = "2019";
    const char *argv[] = {progname, "-a", artist, "-A", album, "-g", genre, "-y", year, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Variables *vars = argparser.getVariables();
    Tagger tagger(vars);

    // When tagging a file copy
    string new_filepath = dl_tmp + "currently-tested.mp3";
    fs::copy(filepath, new_filepath);
    tagger.tag(new_filepath);

    // Then the file tags must be those of the command
    TagLib::FileRef file = tagger.getTaggedFile();
    BOOST_TEST(file.tag()->artist().toCString() == artist);
    BOOST_TEST(file.tag()->album().toCString() == album);
    BOOST_TEST(file.tag()->genre().toCString() == genre);
    BOOST_TEST(file.tag()->year() == stoi(year));
    fs::remove(file.file()->name());
}

////////////////////////////////////////////////////////
// Parse command, extract, and tag tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(extract_artist_command_tag)
{
    // Given a test file with artist field
    const string new_filepath = dl_tmp + "great artist - currently-tested.mp3";
    fs::copy(filepath, new_filepath);
    // and a command to extract the artist
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command, extracting and tagging the file
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    extractor.setFile(new_filepath);
    extractor.extract();
    Tagger tagger(extractor.getVariables());
    tagger.tag(new_filepath);

    // Then the file artist and title tags must be those ones
    TagLib::FileRef file = tagger.getTaggedFile();
    BOOST_TEST(file.tag()->artist().toCString() == "great artist");
    BOOST_TEST(file.tag()->title().toCString() == "currently-tested");
    fs::remove(file.file()->name());
}

BOOST_AUTO_TEST_CASE(extract_no_artist_command_tag)
{
    // Given a test file without artist field
    string new_filepath = dl_tmp + "currently-tested.mp3";
    fs::copy(filepath, new_filepath);
    // and a command to extract the artist
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command, extracting and tagging the file
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    extractor.setFile(new_filepath);
    extractor.extract();
    Tagger tagger(extractor.getVariables());
    tagger.tag(new_filepath);

    // Then the file artist and title tags must be those ones
    TagLib::FileRef file = tagger.getTaggedFile();
    BOOST_TEST(file.tag()->artist().toCString() == language.unknown().c_str());
    BOOST_TEST(file.tag()->title().toCString() == "currently-tested");
    fs::remove(file.file()->name());
}

BOOST_AUTO_TEST_CASE(track_tag)
{
    // Given a test file with track field
    string new_filepath = dl_tmp + "17_great artist - currently-tested.mp3";
    fs::copy(filepath, new_filepath);
    // and the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command, extracting and tagging the file
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    extractor.setFile(new_filepath);
    extractor.extract();
    Tagger tagger(extractor.getVariables());
    tagger.tag(new_filepath);

    // Then the file track, artist and title tags must be those ones
    TagLib::FileRef file = tagger.getTaggedFile();
    BOOST_TEST(file.tag()->track() == 17);
    BOOST_TEST(file.tag()->artist().toCString() == language.unknown().c_str());
    BOOST_TEST(file.tag()->title().toCString() == "great artist - currently-tested");
    fs::remove(file.file()->name());
}

BOOST_AUTO_TEST_CASE(track_and_extract_artist_tag)
{
    // Given a test file with track field
    string new_filepath = dl_tmp + "17_great artist - currently-tested.mp3";
    fs::copy(filepath, new_filepath);
    // and a command to extract the artist
    const char *argv[] = {progname, "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);

    // When parsing the command, extracting and tagging the file
    ArgParser argparser(argc, argv);
    Extractor extractor = Extractor(argparser.getVariables());
    extractor.setFile(new_filepath);
    extractor.extract();
    Tagger tagger(extractor.getVariables());
    tagger.tag(new_filepath);

    // Then the file track, artist and title tags must be those ones
    TagLib::FileRef file = tagger.getTaggedFile();
    BOOST_TEST(file.tag()->track() == 17);
    BOOST_TEST(file.tag()->artist().toCString() == "great artist");
    BOOST_TEST(file.tag()->title().toCString() == "currently-tested");
    fs::remove(file.file()->name());
}

BOOST_AUTO_TEST_SUITE_END()