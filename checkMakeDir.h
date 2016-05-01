#ifndef CHECKMAKEDIR_H
#define CHECKMAKEDIR_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};

void checkMakeDir(const std::string inPath)
{
  if(stat(inPath.c_str(), &st) == -1) {
    mkdir(inPath.c_str(), 0700);
  }

  return;
}

#endif
