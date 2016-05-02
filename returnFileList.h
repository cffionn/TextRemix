#ifndef RETURNFILELIST_H
#define RETURNFILELIST_H

#include <iostream>

#include <vector>
#include <string>

#include "dirent.h"
#include "sys/stat.h"

#include "checkMakeDir.h"

std::vector<std::string> returnFileList(std::string dirPath, const std::string filterStr = ".txt")
{
  bool doFilter = true;
  if(!strcmp(filterStr.c_str(), "")) doFilter = false;

  std::vector<std::string> fileList;

  DIR *dpdf = opendir(dirPath.c_str());
  struct dirent *epdf;

  std::string interString = "";
  if(strcmp(dirPath.substr(dirPath.size()-1, 1).c_str(), "/") != 0) interString = "/";

  if(dpdf != NULL){
    epdf = readdir(dpdf);
    while(epdf){
      std::string tempStr = epdf->d_name;

      if(!strcmp(tempStr.c_str(), ".")){
	epdf = readdir(dpdf);
	continue;
      }
      else if(!strcmp(tempStr.c_str(), "..")){
	epdf = readdir(dpdf);
	continue;
      }

      std::string fullStr = dirPath + interString + tempStr;

      if(checkDir(fullStr)){
	std::vector<std::string> tempStrVect = returnFileList(fullStr);
        for(int iter = 0; iter < (int)tempStrVect.size(); iter++){
          if(tempStrVect.at(iter).find(filterStr.c_str()) != std::string::npos || !doFilter) fileList.push_back(tempStrVect.at(iter));
        }
      }
      else{
        if(fullStr.find(filterStr.c_str()) != std::string::npos || !doFilter) fileList.push_back(fullStr);
      }

      epdf = readdir(dpdf);
    }
  }
  else{
    std::cout << "NULL PATH" << std::endl;
    return fileList;
  }

  return fileList;
}

#endif
