#ifndef PARSEYESNO_H
#define PARSEYESNO_H

#include <iostream>
#include <string>

#include "interface/globalDoDebug.h"
#include "interface/defAlphaNumSoup.h"

#include <boost/algorithm/string.hpp>

bool isYesNo(std::string input)
{
  if(input.size() == 0){
    std::cout << "No input give. Please choose y/n." << std::endl;
    return false;
  }

  for(int iter = 0; iter < (int)input.size(); iter++){
    if(alphabetSoup.find(input.at(iter)) == std::string::npos){
      std::cout << "Input not alphabet. Please choose y/n" << std::endl;
      return false;
    }
  }

  boost::algorithm::to_lower(input);
  if(input.find("y") != std::string::npos && input.size() == 1) return true;
  if(input.find("n") != std::string::npos && input.size() == 1) return true;
  if(input.find("yes") != std::string::npos && input.size() == 3) return true;
  if(input.find("no") != std::string::npos && input.size() == 2) return true;

  return false;
}

#endif
