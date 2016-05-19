#ifndef CHECKOUTPUTTXTFILE_H
#define CHECKOUTPUTTXTFILE_H

#include <iostream>
#include <string>

#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"

bool checkOutputTxtFile(const std::string inFileName)
{
  if((int)inFileName.size() < 4){
    std::cout << "inFileName \'" << inFileName << "\' needs to be at least four characters for \'.txt\'. Return false" << std::endl;
    return false;
  }
  
  if(inFileName.substr(inFileName.size()-4, 4).find(".txt") == std::string::npos){
    std::cout << "inFileName \'" << inFileName << "\' needs to be \'.txt\'. Return false" << std::endl;
    return false;
  }
  
  if(inFileName.substr(0, 6).find("output") == std::string::npos){
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
