#include "files_manager.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/foreach.hpp>
using namespace std;
namespace fs = boost::filesystem;

FilesManager::FilesManager(Variables *vars, const string &dl_dir)
{
    this->vars = vars;
    this->dl_dir = dl_dir;
    this->extractor = Extractor(vars);
    this->tagger = Tagger(vars);
}

FilesManager::~FilesManager() {}

void FilesManager::manageDownloadDir()
{
    path dl_dir_path(dl_dir);
    directory_iterator dl_dir_iterator(dl_dir_path), eod;
    BOOST_FOREACH (path const &p, make_pair(dl_dir_iterator, eod))
    {
        if (is_regular_file(p))
        {
            manageFile(p);
        }
    }
    fs::remove_all(dl_dir_path);
}

void FilesManager::manageFile(const path &filepath)
{
    extractor.setFile(filepath);
    extractor.extract();
    tagger.tag(filepath);
    moveFile(filepath);
}

void FilesManager::moveFile(const path &filepath)
{
    string title = vars->getTitle();
    if (!title.empty())
    {
        string new_stem = removeSpaces(title);
        string ext = filepath.filename().extension().string();
        string new_path = vars->getDestDir() + "/" +
                          vars->getArtist() + "/" +
                          vars->getAlbum() + "/";
        fs::create_directories(new_path);
        string new_filepath = new_path + new_stem + ext;
        fs::rename(filepath, new_filepath); // move renamed file in its music directory
    }
    else
    {
        cerr << "title is empty so not renaming file '" << filepath.filename().string() << "'\n";
    }
}