#include <boost/test/unit_test.hpp>
#include "../src/argparser.hpp"
#include "../src/files_manager.hpp"
using namespace std;
namespace fs = boost::filesystem;

BOOST_AUTO_TEST_SUITE(FilesManagerTestSuite)

const char *progname = "music-dl";
const char *url = "http://music-adress";
Language language(Lang::FR);
const string dl_dir = "dl";
const string test_dl_dir = "test_dl";
const string filename = "test-audio-file.mp3";
const string filepath = dl_dir + "/" + filename;
const string dest_dir = "dest";

BOOST_AUTO_TEST_CASE(move_file)
{
    // Given a destination directory and a test file
    string new_filepath = test_dl_dir + "/currently-tested.mp3";
    fs::create_directory(test_dl_dir);
    fs::copy(filepath, new_filepath);
    // and a command with the destination directory
    const char *argv[] = {progname, "-d", dest_dir.c_str(), url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Variables *vars = argparser.getVariables();

    // When managing the file
    FilesManager files_manager(vars, test_dl_dir);
    files_manager.manageFile(new_filepath);

    // It must be in the appropriate directory
    string dest_path = dest_dir + "/" + language.unknown() + "/" + language.unknown() + "/";
    string dest_filepath = dest_path + "currently-tested.mp3";
    BOOST_TEST(fs::exists(dest_filepath));
    fs::remove_all(dest_dir + "/" + language.unknown());
    fs::remove_all(test_dl_dir);
}

BOOST_AUTO_TEST_CASE(rename_and_move_file)
{
    // Given a destination directory and a test file with spaces
    string new_filepath = test_dl_dir + "/ currently tested .mp3";
    fs::create_directory(test_dl_dir);
    fs::copy(filepath, new_filepath);
    // and a command with the destination directory
    const char *argv[] = {progname, "-d", dest_dir.c_str(), url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Variables *vars = argparser.getVariables();

    // When managing the file
    FilesManager files_manager(vars, test_dl_dir);
    files_manager.manageFile(new_filepath);

    // It must be renamed and in the appropriate directory
    string dest_path = dest_dir + "/" + language.unknown() + "/" + language.unknown() + "/";
    string dest_filepath = dest_path + "currentlytested.mp3";
    BOOST_TEST(fs::exists(dest_filepath));
    fs::remove_all(dest_dir + "/" + language.unknown());
    fs::remove_all(test_dl_dir);
}

BOOST_AUTO_TEST_CASE(artist_album_move_file)
{
    // Given a destination directory and a test file
    string new_filepath = test_dl_dir + "/currently-tested.mp3";
    fs::create_directory(test_dl_dir);
    fs::copy(filepath, new_filepath);
    // and a command with the destination directory and artist and album tags
    const string artist = "Ray Blue";
    const string album = "Work";
    const char *argv[] = {progname, "-d", dest_dir.c_str(),
                          "-a", artist.c_str(), "-A", album.c_str(), url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Variables *vars = argparser.getVariables();

    // When managing the file
    FilesManager files_manager(vars, test_dl_dir);
    files_manager.manageFile(new_filepath);

    // It must be in the appropriate directory
    string dest_path = dest_dir + "/" + artist + "/" + album + "/";
    string dest_filepath = dest_path + "currently-tested.mp3";
    BOOST_TEST(fs::exists(dest_filepath));
    fs::remove_all(dest_dir + "/" + artist);
    fs::remove_all(test_dl_dir);
}

BOOST_AUTO_TEST_CASE(extract_artist_move_file)
{
    // Given a destination directory and a test file
    string new_filepath = test_dl_dir + "/ Ray Blue - currently-tested.mp3";
    fs::create_directory(test_dl_dir);
    fs::copy(filepath, new_filepath);
    // and a command with the destination directory and artist and album tags
    const char *argv[] = {progname, "-d", dest_dir.c_str(), "--extract-artist", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Variables *vars = argparser.getVariables();

    // When managing the file
    FilesManager files_manager(vars, test_dl_dir);
    files_manager.manageFile(new_filepath);

    // It must be in the appropriate directory
    string dest_path = dest_dir + "/" + "Ray Blue/" + language.unknown() + "/";
    string dest_filepath = dest_path + "currently-tested.mp3";
    BOOST_TEST(fs::exists(dest_filepath));
    fs::remove_all(dest_dir + "/Ray Blue");
    fs::remove_all(test_dl_dir);
}

BOOST_AUTO_TEST_SUITE_END()
