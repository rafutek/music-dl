## About

This C++ program is a [youtube-dl](https://github.com/ytdl-org/youtube-dl) wrapper to make downloading music easier from YouTube, SoundCloud and [other websites](https://github.com/ytdl-org/youtube-dl/blob/master/docs/supportedsites.md).

In addition of youtube-dl options, the files are tagged and moved into the artist/album folders.

``` txt
music-dl is a program for GNU/Linux users to download and tag music.

Usage: music-dl [OPTIONS] URL

Options:
  -h [ --help ]           Print this help message
  -l [ --lang ] arg       Set language for unknown tags 
                          choices: ['en', 'fr'] (locale or 'en' by default)
  -c [ --cover-path ] arg Set cover from local image
  --extract-cover         Extract the cover from the website
  -a [ --artist ] arg     Set artist name tag
  --extract-artist        Extract artist name from music titles
  -A [ --album ] arg      Set album name tag
  -g [ --genre ] arg      Set album genre tag
  -y [ --year ] arg       Set album year tag
  -d [ --dest-dir ] arg   Set destination directory
  -r [ --remove-ex ] arg  Remove expression from titles
                          (option can be used multiple times)
  -f [ --format ] arg     Set audio format
                          choices: ['mp3', 'flac'] ('mp3' by default)
```

## Install

- Clone or dowload this repository.
- Make sure [Boost](https://www.boost.org/) and [TagLib](https://taglib.org/) libraries are installed on your system. On Debian, install them with `sudo apt-get install libboost-all-dev libtag1-dev`.
- Compile and run the tests (optional).
- Install music-dl executing `make install` from src/ folder. It will store it in your **~/.local/bin** directory.
- Open a new terminal and check with `music-dl -h`. If the help message is not displayed, you must add **~/.local/bin** to your PATH variable.


## First steps

- Create a test directory with `mkdir test_dir`.
- After `cd test_dir`, execute `music-dl https://www.youtube.com/watch?v=FSRipXBJqcc`.
- Finally, check thre result with `tree`. You can also open the downloaded file with your music player to see the tags.
- You can redo these steps adding options to the command.