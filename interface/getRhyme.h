#ifndef GETRHYME_H
#define GETRHYME_H

#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>    

#include "interface/defAlphaNumSoup.h"
#include "interface/returnFileList.h"

const std::string rhymeDatabasePath = "rhymeDatabase/";

const std::string noRhymeStr = "noRhyme";


int orderRhymeFileList(std::vector<std::string>* fileList_p)
{
  const int nRhymeFiles = (int)fileList_p->size();

  if(nRhymeFiles == 0){
    std::cout << "Input list of rhyme files empty. Please give non-empty list of rhyme files" << std::endl;
    return -1;
  }
  else{
    int pos = -1;
    for(int iter = 0; iter < nRhymeFiles; iter++){
      if(fileList_p->at(iter).find(noRhymeStr) != std::string::npos){
	pos = iter;
	break;
      }
    }

    if(pos == -1){
      std::cout << "Input list of rhyme files does not contain noRhyme file. Return -1." << std::endl;
      return -1;
    }
    else{

      for(int iter = pos; iter < (int)fileList_p->size()-1; iter++){
	std::string tempString = fileList_p->at(iter);
	fileList_p->at(iter) = fileList_p->at(iter+1);
	fileList_p->at(iter+1) = tempString;
      }

    }
  }

  return 0;
}

int getRhyme(std::string inWord, std::vector<std::string>* fileList_p, bool doInteractiveRhyme)
{
  boost::algorithm::to_lower(inWord);

  int rhymeNum = -1;

  const int nRhymeFiles = (int)fileList_p->size();

  if(nRhymeFiles == 0){
    std::cout << "Input list of rhyme files empty. Please give non-empty list of rhyme files" << std::endl;
    return -1;
  }
  else if(fileList_p->at(nRhymeFiles-1).find(noRhymeStr) == std::string::npos){
    std::cout << "noRhyme file not last in list. Swapping." << std::endl;
    if(orderRhymeFileList(fileList_p) == -1){
      return -1;
    }
  }

  for(int rhymeIter = 0; rhymeIter < nRhymeFiles; rhymeIter++){
    std::ifstream file(fileList_p->at(rhymeIter).c_str());
    std::string str;
    bool breakBool = false;

    while(std::getline(file, str)){
      boost::algorithm::to_lower(str);
      if(!strcmp(inWord.c_str(), str.c_str())){
	rhymeNum = rhymeIter;
	breakBool = true;
	break;
      }
    }
    file.close();    
    if(breakBool) break;
  }

  while(rhymeNum == -1){
    if(doInteractiveRhyme){
      std::cout << "Word not found. Please enter integer corresponding to rhyme file (0-" << nRhymeFiles-1 << ") of \'" << inWord << "\': " << std::endl;
      
      for(int rhymeIter = 0; rhymeIter < nRhymeFiles; rhymeIter++){
	std::string rhymingWord =  fileList_p->at(rhymeIter).substr(0, fileList_p->at(rhymeIter).find(".txt"));
	rhymingWord = rhymingWord.substr(rhymingWord.find("/")+1, rhymingWord.find("/")+1-rhymingWord.size());
	
	std::cout << " Input " << rhymeIter << ": " << rhymingWord << " (" << inWord << ")" << std::endl;
      }
      
      std::cout << " Enter num: ";
      int input;
      std::cin >> input;
      if(!(std::cin.good())){
	std::cout << "Input was not integer. Please enter integer 0 thru " << nRhymeFiles-1 << "." << std::endl;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
      }
      else if(input < 0) std::cout << "Input less than 0. Please enter integer 0 thru " << nRhymeFiles-1 << "." << std::endl;
      else if(input > nRhymeFiles-1) std::cout << "Input greater than " << nRhymeFiles-1 << ". Please enter integer 0 thru "<< nRhymeFiles-1 <<"." << std::endl;
      else{
	rhymeNum = input;
	std::fstream file(fileList_p->at(rhymeNum).c_str(), std::fstream::app);
	file << inWord << std::endl;
	file.close();
      }			
    }
    else{
      rhymeNum = nRhymeFiles-1;
      std::fstream file(fileList_p->at(rhymeNum).c_str(), std::fstream::app);
      file << inWord << std::endl;
      file.close();
    }      
  }
  
  return rhymeNum;
}

#endif
