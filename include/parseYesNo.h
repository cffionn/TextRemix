#ifndef PARSEYESNO_H
#define PARSEYESNO_H

#include <iostream>
#include <string>

#include "include/globalDoDebug.h"
#include "include/defAlphaNumSoup.h"

#include <boost/algorithm/string.hpp>

bool isYesNo(std::string input)
{
  if(input.size() == 0){
    std::cout << "No input given. Please choose y/n." << std::endl;
    return false;
  }

  for(int iter = 0; iter < (int)input.size(); iter++){
    if(alphabetSoup.find(input.at(iter)) == std::string::npos){
      std::cout << "Input \'" << input << "\' not alphabet. Please choose y/n." << std::endl;
      return false;
    }
  }

  boost::algorithm::to_lower(input);
  if(input.find("y") != std::string::npos && input.size() == 1) return true;
  if(input.find("n") != std::string::npos && input.size() == 1) return true;
  if(input.find("yes") != std::string::npos && input.size() == 3) return true;
  if(input.find("no") != std::string::npos && input.size() == 2) return true;

  std::cout << "Input \'" << input << "\' not y/n. Please choose y/n." << std::endl;

  return false;
}

//return 1 if yes; 0 if no; -1 if invalid
int parseYesNo(std::string input)
{
  if(!isYesNo(input)) return -1;
  boost::algorithm::to_lower(input);

  if(input.find("y") != std::string::npos && input.size() == 1) return 1;
  else if(input.find("yes") != std::string::npos && input.size() == 3) return 1;
  else if(input.find("n") != std::string::npos && input.size() == 1) return 0;
  else if(input.find("no") != std::string::npos && input.size() == 2) return 0;

  std::cout << "Error with parse/isYesNo for input \'" << input << "\'. Please check. Return -1." << std::endl;
  return -1;
}

#endif
