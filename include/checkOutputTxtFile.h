#ifndef CHECKOUTPUTTXTFILE_H
#define CHECKOUTPUTTXTFILE_H

#include <iostream>
#include <string>

#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"

bool checkOutputTxtFile(const std::string inFileName)
{
  std::string tempInFileName = inFileName;
  int nDashes = 0;

  while(tempInFileName.find("/") != std::string::npos){
    nDashes++;
    tempInFileName.replace(0, tempInFileName.find("/")+1, "");
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  tempInFileName = inFileName;
  int dashIter = 0;
  while(dashIter < nDashes-1){
    tempInFileName.replace(0, tempInFileName.find("/")+1, "");
    dashIter++;
  }

  if((int)tempInFileName.size() < 4){
    std::cout << "inFileName \'" << inFileName << "\' needs to be at least four characters for \'.txt\'. Return false" << std::endl;
    return false;
  }
  
  if(tempInFileName.substr(tempInFileName.size()-4, 4).find(".txt") == std::string::npos){
    std::cout << "inFileName \'" << inFileName << "\' needs to be \'.txt\'. Return false" << std::endl;
    return false;
  }
  
  if(tempInFileName.substr(0, 6).find("output") == std::string::npos){
    std::cout << "inFileName \'" << inFileName << "\' must be output*/*.txt. Return false" << std::endl;
    return false;
  }
  
  if(!checkFile(inFileName)){
    std::cout << "inFileName \'" << inFileName << "\' not a file. Return false" << std::endl;
    return false;
  }

  return true;
}

#endif
