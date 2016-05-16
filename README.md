# TextRemix

TextRemix is C++ code for creation of new text from two input sources, by matching words and then replacing. Makes use of boost for some simple string manipulation + randomization, otherwise no libraries needed

To Build
  In a clean directory, run:

    git clone https://github.com/cffionn/TextRemix
    cd TextRemix
    make

  At this point should be built; Please contact for errors.

To Run
  

To cleanup executables, backups, etc.:
  In ~\TextRemix run:

    make clean

  All executables, outputDirs, and ~ or # backups should be cleaned. Please run this before pushing (local git config should exclude, but just in case)

To compile individual file w/o make:
  In ~\TextRemix run:

    sh compile.sh src\<.C file\>

./\<Created .exe File\> \<input args\>

where \<input args\> will be requested as prompt when running ./<.C File> with no arguments

example:

sh compile.sh createNewIdioms.C

./createNewIdioms.exe \<inputTxtFile1\> \<inputTxtFile2\>