#ifndef GETSYLLABLE_H
#define GETSYLLABLE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>    

#include "include/globalDoDebug.h"
#include "include/defAlphaNumSoup.h"
#include "include/getWordsFromSentence.h"

const int nSylFiles = 8;
const std::string sylFileStrings[nSylFiles] = {"syllableDatabase/oneSyllable.txt", "syllableDatabase/twoSyllable.txt", "syllableDatabase/threeSyllable.txt", "syllableDatabase/fourSyllable.txt", "syllableDatabase/fiveSyllable.txt", "syllableDatabase/sixSyllable.txt", "syllableDatabase/sevenSyllable.txt", "syllableDatabase/eightSyllable.txt"};

int getSyllable(std::string inWord)
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
    if(!(std::cin.good())){
      std::cout << "Input was not integer. Please enter integer 1 thru 8." << std::endl;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
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

int getSyllables(std::string inSentence)
{
  int syllables = 0;

  std::vector<std::string>* sentenceWords_p = new std::vector<std::string>;

  getWordsFromSentence(inSentence, sentenceWords_p);

  for(int iter = 0; iter < (int)sentenceWords_p->size(); iter++){
    if(sentenceWords_p->at(iter).size() == 0) continue;
    syllables += getSyllable(sentenceWords_p->at(iter));
  }

  sentenceWords_p->clear();
  delete sentenceWords_p;

  return syllables;
}

int getNWords(std::string inSentence)
{
  int nWords = 0;

  std::vector<std::string>* sentenceWords_p = new std::vector<std::string>;

  getWordsFromSentence(inSentence, sentenceWords_p);

  for(int iter = 0; iter < (int)sentenceWords_p->size(); iter++){
    if(sentenceWords_p->at(iter).size() == 0) continue;
    nWords++;
  }

  sentenceWords_p->clear();
  delete sentenceWords_p;

  return nWords;
}

#endif
