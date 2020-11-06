#include "downloader.hpp"
#include "format.hpp"
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <iostream>
#include <string>
namespace fs = boost::filesystem;
namespace bp = boost::process;
using namespace std;

/**
 * Constructor used to set local download variables.
 */
Downloader::Downloader(const Variables *vars)
{
    this->vars = vars;
    this->dl_directory = ".music_dl";
    this->executable = bp::search_path("youtube-dl");
}

Downloader::~Downloader() {}

const string Downloader::getDownloadDir() const { return dl_directory; }

/**
 * Downloads music into a temporary directory depending on the variables. 
 * Quit if download error.
 */
void Downloader::download()
{
    const string dl_dir_name = this->getDownloadDir();
    fs::remove_all(dl_dir_name);
    fs::create_directory(dl_dir_name);

    string command = this->getDownloadCommand();
    int error_code;
    try
    {
        error_code = bp::system(command);
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    if (error_code != 0)
    {
        cerr << "error downloading music\n";
        fs::remove_all(dl_dir_name);
        exit(1);
    }
}

/**
 * Returns the command to be executed depending on the variables.
 */
string Downloader::getDownloadCommand() const
{
    string command = executable.string() + " -x ";
    if (this->vars->extractCover())
    {
        command += "--embed-thumbnail ";
    }
    command += "-o " + getDownloadDir() + "/%(playlist_index)s_%(title)s.%(ext)s ";
    command += "--audio-format " + formatToString(vars->getFormat()) + " ";
    command += vars->getURL();
    return command;
}