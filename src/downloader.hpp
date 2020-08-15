#ifndef DOWNLOADER
#define DOWNLOADER

#include "variables.hpp"
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

/**
 * Download music manager.
 */
class Downloader
{
private:
    const Variables *vars;
    string dl_directory;
    fs::path executable;

public:
    Downloader(const Variables *vars);
    ~Downloader();
    void download();
    const string getDownloadDir() const;
    string getDownloadCommand() const;
};

#endif