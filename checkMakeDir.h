#ifndef CHECKMAKEDIR_H
#define CHECKMAKEDIR_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};

bool checkDir(const std::string inPath)
{

  if(stat(inPath.c_str(), &st) != 0) return false;

  if(st.st_mode & S_IFDIR) return true;
  else return false;
}

bool checkFile(const std::string inFile)
{
  if(stat(inFile.c_str(), &st) != 0) return false;

  if(st.st_mode & S_IFREG) return true;
  else return false;
}


void checkMakeDir(const std::string inPath)
{
  if(!checkDir(inPath)){
    mkdir(inPath.c_str(), 0700);
  }

  return;
}

#endif
