#ifndef FILES_MANAGER
#define FILES_MANAGER

#include "variables.hpp"
#include "tagger.hpp"
#include "extractor.hpp"
#include <string>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

class FilesManager
{
private:
    string dl_dir;
    Variables *vars;
    Tagger tagger;
    Extractor extractor;

    void moveFile(const path &filepath);

public:
    FilesManager(Variables *vars, const string &dl_dir);
    ~FilesManager();
    void manageDownloadDir();
    void manageFile(const path &filepath);
};

#endif