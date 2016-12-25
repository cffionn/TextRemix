#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>

#include "include/globalDoDebug.h"
#include "include/checkOutputTxtFile.h"
#include "include/getWordsFromSentence.h"

int myrandom(int i){return std::rand()%i;}

int createSimplePoem(const std::string inFileName)
{
  if(!checkOutputTxtFile(inFileName)) return -1;

  std::ifstream inFile(inFileName);
  std::string str;
  std::vector<std::string>* strVect_p = new std::vector<std::string>;

  while(std::getline(inFile, str)){
    strVect_p->push_back(str);
  }
  inFile.close();

  std::srand(unsigned(std::time(NULL)));
  std::random_shuffle(strVect_p->begin(), strVect_p->end(), myrandom);

  std::vector<std::string>* poemVect_p = new std::vector<std::string>;
  
  bool outOfMatches = false;
  while((int)poemVect_p->size() < 10){

    int strSize = (int)strVect_p->size();
    
    bool isMatch = false;
    for(int iter = 0; iter < strSize-1; iter++){
      std::string sentence1 = strVect_p->at(iter);
      std::vector<std::string>* words1_p = new std::vector<std::string>;

      getWordsFromSentence(sentence1, words1_p);

      for(int iter2 = 1; iter2 < strSize; iter2++){
	std::string sentence2 = strVect_p->at(iter2);
	std::vector<std::string>* words2_p = new std::vector<std::string>;

	getWordsFromSentence(sentence2, words2_p);

	for(int wordIter1 = 0; wordIter1 < (int)words1_p->size(); wordIter1++){
	  std::string word1 = words1_p->at(wordIter1);

	  for(int wordIter2 = 0; wordIter2 < (int)words2_p->size(); wordIter2++){
	    std::string word2 = words2_p->at(wordIter2);

	    if(word1.find(word2) != std::string::npos || word2.find(word1) != std::string::npos){
	      isMatch = true;
	      break;
	    }
	  }
	  if(isMatch) break;
	}

	if(isMatch){
	  poemVect_p->push_back(sentence1);
	  poemVect_p->push_back(sentence2);

	  strVect_p->erase(strVect_p->begin()+iter2);
	  strVect_p->erase(strVect_p->begin()+iter);
	}
	else if(iter == strSize - 2) outOfMatches = true;

	words2_p->clear();
	delete words2_p;

	if(isMatch) break;
      }


      words1_p->clear();
      delete words1_p;


      if(isMatch) break;
    }
  
    if(outOfMatches) break;
  }


  std::string outFileName = inFileName;
  outFileName.replace(outFileName.find(".txt"), 4, "");
  outFileName = outFileName + "_SimplePoem.txt";

  std::ofstream outFile(outFileName);
  for(int iter = 0; iter < (int)poemVect_p->size(); iter++){
    outFile << poemVect_p->at(iter) << std::endl;
  }
  outFile.close();

  poemVect_p->clear();
  delete poemVect_p;

  strVect_p->clear();
  delete strVect_p;

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: createSimplePoem.exe <inputFile>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int result = createSimplePoem(argv[1]);

  return result;
}
