#include "argparser.hpp"
#include "variables.hpp"
#include "downloader.hpp"
#include "files_manager.hpp"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    ArgParser argparser(argc, argv);
    Variables *vars = argparser.getVariables();
    if (!vars->areCompatible())
    {
        cerr << "some variables are not compatible\n";
        exit(1);
    }

    Downloader downloader(vars);
    downloader.download();

    FilesManager files_manager(vars, downloader.getDownloadDir());
    files_manager.manageDownloadDir();

    return 0;
}