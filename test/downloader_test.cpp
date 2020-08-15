#include <boost/test/unit_test.hpp>
#include "../src/argparser.hpp"
#include "../src/downloader.hpp"
using namespace std;

BOOST_AUTO_TEST_SUITE(DownloaderTestSuite)

const char *progname = "music-dl";
const char *url = "http://test-music-adress";
Language language(Lang::FR);
const string executable = "/usr/local/bin/youtube-dl";


BOOST_AUTO_TEST_CASE(dl_dir)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Downloader downloader(argparser.getVariables());

    // Then download dir must be this one
    BOOST_TEST(downloader.getDownloadDir() == ".music_dl");
}

BOOST_AUTO_TEST_CASE(basic_dl_command)
{
    // Given the basic command
    const char *argv[] = {progname, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Downloader downloader(argparser.getVariables());

    // Then the basic command must be this one
    string out = downloader.getDownloadDir() + "/%(playlist_index)s_%(title)s.%(ext)s ";
    string format = "--audio-format mp3 ";
    string basic_command = executable + " -x -o " + out + format + url;
    BOOST_TEST(downloader.getDownloadCommand() == basic_command);
}

////////////////////////////////////////////////////////
// Audio format tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(command_mp3_format)
{
    // Given a command with flac format option
    const char *argv[] = {progname, "-f", "mp3", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Downloader downloader(argparser.getVariables());

    // Then the command must have mp3 format option
    string out = downloader.getDownloadDir() + "/%(playlist_index)s_%(title)s.%(ext)s ";
    string format = "--audio-format mp3 ";
    string mp3_command = executable + " -x -o " + out + format + url;
    // BOOST_TEST(downloader.getDownloadCommand() == mp3_command);
}

BOOST_AUTO_TEST_CASE(command_flac_format)
{
    // Given a command with flac format option
    const char *argv[] = {progname, "-f", "flac", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Downloader downloader(argparser.getVariables());

    // Then the command must have flac format option
    string out = downloader.getDownloadDir() + "/%(playlist_index)s_%(title)s.%(ext)s ";
    string format = "--audio-format flac ";
    string flac_command = executable + " -x -o " + out + format + url;
    // BOOST_TEST(downloader.getDownloadCommand() == flac_command);
}

////////////////////////////////////////////////////////
// Cover tests
////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(command_extract_cover)
{
    // Given a command with extract cover option
    const char *argv[] = {progname, "--extract-cover", url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Downloader downloader(argparser.getVariables());

    // Then the command must have extract cover option
    string out = downloader.getDownloadDir() + "/%(playlist_index)s_%(title)s.%(ext)s ";
    string format = "--audio-format mp3 ";
    string extract_cover = "--embed-thumbnail";
    string cover_command = executable + " -x " + extract_cover + " -o " + out + format + url;
    // BOOST_TEST(downloader.getDownloadCommand() == cover_command);
}

BOOST_AUTO_TEST_CASE(command_cover_path)
{
    // Given a command with cover path option
    const char *coverpath = "./test.jpg";
    const char *argv[] = {progname, "-c", coverpath, url};
    const unsigned int argc = sizeof(argv) / sizeof(*argv);
    ArgParser argparser(argc, argv);
    Downloader downloader(argparser.getVariables());

    // Then the command must not have extract cover option
    string out = downloader.getDownloadDir() + "/%(playlist_index)s_%(title)s.%(ext)s ";
    string format = "--audio-format mp3 ";
    string basic_command = executable + " -x -o " + out + format + url;
    // BOOST_TEST(downloader.getDownloadCommand() == basic_command);
}

BOOST_AUTO_TEST_SUITE_END()