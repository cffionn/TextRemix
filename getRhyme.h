#ifndef GETRHYME_H
#define GETRHYME_H

#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>    

#include "defAlphaNumSoup.h"


std::vector<std::string> returnFileList(std::string dirPath)
{
  std::vector<std::string>* fileList_p = new std::vector<std::string>;

  return fileList_p;
}


int getRhyme(std::string inWord, std::vector<std::string>* fileList_p)
{
  boost::algorithm::to_lower(inWord);

  int syllable = -1;

  for(int sylIter = 0; sylIter < nSylFiles; sylIter++){
    std::ifstream file(sylFileStrings[sylIter].c_str());
    std::string str;
    bool breakBool = false;

    while(std::getline(file, str)){
      boost::algorithm::to_lower(str);
      if(!strcmp(inWord.c_str(), str.c_str())){
	syllable = sylIter+1;
	breakBool = true;
	break;
      }
    }
    file.close();    
    if(breakBool) break;
  }  

  while(syllable == -1){
    std::cout << "Word not found. Please enter integer corresponding to number of syllables (1-8) in \'" << inWord << "\': ";
    int input;
    std::cin >> input;
    if(std::cin.fail()){
      std::cout << "Input was not integer. Please enter integer 1 thru 8." << std::endl;
    }
    else if(input < 1) std::cout << "Input less than 1. Please enter integer 1 thru 8." << std::endl;
    else if(input > 8) std::cout << "Input greater than 8. Please enter integer 1 thru 8." << std::endl;
    else{
      std::fstream file(sylFileStrings[input-1].c_str(), std::fstream::app);
      file << inWord << std::endl;
      file.close();
      syllable = input;
    }			      
  }
  
  return syllable;
}

#endif
