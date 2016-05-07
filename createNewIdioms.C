#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <algorithm> 
#include <cstdlib>
#include <ctime>

#include <boost/algorithm/string.hpp>

#include "interface/defAlphaNumSoup.h"
#include "interface/checkMakeDir.h"

const std::string outDirFull = "outputFull/";
const std::string outDirTweet = "outputTweet/";

int myrandom(int i){return std::rand()%i;}

int createNewIdioms(const std::string inFileName, const std::string inFileName2, const std::string outName, bool doAppend)
{

  std::ifstream file;
  std::string str; 

  std::vector<std::string>* inStr1_p = new std::vector<std::string>;
  std::vector<std::string>* inStr2_p = new std::vector<std::string>;
  std::vector<std::string>* totalWords_p = new std::vector<std::string>;


  if(inFileName.find(".txt") != std::string::npos){
    file.open(inFileName.c_str());
    while(std::getline(file, str)){
      inStr1_p->push_back(str);
    }
    file.close();
  }
  else{
    std::cout << "inFileName 1, \'" << inFileName << "\' is invalid. Not \'.txt\'. Return 1." << std::endl;
    return 1;
  }

  if(inFileName2.find(".txt") != std::string::npos){
    file.open(inFileName2.c_str());
    while(std::getline(file, str)){
      inStr2_p->push_back(str);
    }
    file.close();
  }
  else{
    std::cout << "inFileName 2, \'" << inFileName2 << "\' is invalid. Not \'.txt\'. Return 1." << std::endl;
    return 1;
  }

  if(inStr1_p->size() == 0){
    std::cout << "Input file 1 empty. Return 1" << std::endl;
    return 1;
  }

  if(inStr2_p->size() == 0){
    std::cout << "Input file 2 empty. Return 1" << std::endl;
    return 1;
  }

  std::vector<std::string>* newStr_p = new std::vector<std::string>;

  const int inStr1Size = (int)inStr1_p->size();
  const int inStr2Size = (int)inStr2_p->size();
  for(int iter = 0; iter < inStr1Size; iter++){
    std::vector<std::string>* inStr1Words_p = new std::vector<std::string>;
    std::string tempStr = inStr1_p->at(iter);

    while(true){
      std::size_t tempPos = tempStr.find(" ");
      if(tempPos == std::string::npos){
	inStr1Words_p->push_back(tempStr);
	break;
      }
      inStr1Words_p->push_back(tempStr.substr(0, tempPos+1));
      tempStr = tempStr.substr(tempPos+1, tempStr.size()-tempPos+1);
    }

    const int str1WordsSize = (int)inStr1Words_p->size();

    for(int wordIter = 0; wordIter < str1WordsSize; wordIter++){
      bool addWord = true;

      const int totalWordSize = (int)totalWords_p->size(); 
      for(int totalWordIter = 0; totalWordIter < totalWordSize; totalWordIter++){
	if(!strcmp(inStr1Words_p->at(wordIter).c_str(), totalWords_p->at(totalWordIter).c_str())){
	  addWord = false;
	  break;
	}
      }
      if(addWord) totalWords_p->push_back(inStr1Words_p->at(wordIter));
    }

    for(int iter2 = 0; iter2 < inStr2Size; iter2++){
      for(int wordIter = 0; wordIter < str1WordsSize; wordIter++){
	if(inStr2_p->at(iter2).find(inStr1Words_p->at(wordIter)) != std::string::npos){
	  std::size_t pos1 = inStr1_p->at(iter).find(inStr1Words_p->at(wordIter).c_str());
	  std::size_t pos2 = inStr2_p->at(iter2).find(inStr1Words_p->at(wordIter).c_str());

	  std::string newStr = inStr1_p->at(iter).substr(0, pos1) + inStr2_p->at(iter2).substr(pos2, inStr2_p->size() - pos2);
	  newStr_p->push_back(newStr);
	}
      }
    }

    inStr1Words_p->clear();
    delete inStr1Words_p;
  }


  for(int iter = 0; iter < inStr2Size; iter++){
    std::vector<std::string>* inStr2Words_p = new std::vector<std::string>;
    std::string tempStr = inStr2_p->at(iter);

    while(true){
      std::size_t tempPos = tempStr.find(" ");
      if(tempPos == std::string::npos){
	inStr2Words_p->push_back(tempStr);
	break;
      }
      inStr2Words_p->push_back(tempStr.substr(0, tempPos+1));
      tempStr = tempStr.substr(tempPos+1, tempStr.size()-tempPos+1);
    }

    const int str2WordsSize = (int)inStr2Words_p->size();

    for(int wordIter = 0; wordIter < str2WordsSize; wordIter++){
      bool addWord = true;

      const int totalWordSize = (int)totalWords_p->size(); 
      for(int totalWordIter = 0; totalWordIter < totalWordSize; totalWordIter++){
	if(!strcmp(inStr2Words_p->at(wordIter).c_str(), totalWords_p->at(totalWordIter).c_str())){
	  addWord = false;
	  break;
	}
      }
      if(addWord) totalWords_p->push_back(inStr2Words_p->at(wordIter));
    }
  }

  int newIter = 0;
  while(newIter < (int)newStr_p->size()){
    
    bool doIter = true;
    for(int iter = newIter+1; iter < (int)newStr_p->size(); iter++){
      if(!strcmp(newStr_p->at(newIter).c_str(), newStr_p->at(iter).c_str())){
	newStr_p->erase(newStr_p->begin() + iter);
	doIter = false;
	break;
      }
    }
    if(doIter) newIter++;
  }

  newIter = 0;
  while(newIter < (int)newStr_p->size()){
    
    bool doIter = true;
    for(int iter = 0; iter < (int)inStr1_p->size(); iter++){
      if(!strcmp(newStr_p->at(newIter).c_str(), inStr1_p->at(iter).c_str())){
	newStr_p->erase(newStr_p->begin() + newIter);
	doIter = false;
	break;
      }
    }
    if(doIter) newIter++;
  }

  newIter = 0;
  while(newIter < (int)newStr_p->size()){
    
    bool doIter = true;
    for(int iter = 0; iter < (int)inStr2_p->size(); iter++){
      if(!strcmp(newStr_p->at(newIter).c_str(), inStr2_p->at(iter).c_str())){
	newStr_p->erase(newStr_p->begin() + newIter);
	doIter = false;
	break;
      }
    }
    if(doIter) newIter++;
  }

  const int totalWordSize = (int)totalWords_p->size();                                                         
  newIter = 0;
  while(newIter < (int)newStr_p->size()){
    std::vector<std::string>* inStrWords_p = new std::vector<std::string>;
    std::string tempStr = newStr_p->at(newIter);

    while(true){
      std::size_t tempPos = tempStr.find(" ");
      if(tempPos == std::string::npos){
	inStrWords_p->push_back(tempStr);
	break;
      }
      inStrWords_p->push_back(tempStr.substr(0, tempPos+1));
      tempStr = tempStr.substr(tempPos+1, tempStr.size()-tempPos+1);
    }

    const int strWordsSize = (int)inStrWords_p->size();
    bool doIter = true;
    for(int wordIter = 0; wordIter < strWordsSize; wordIter++){
      bool wordPasses = false;
      for(int totalWordIter = 0; totalWordIter < totalWordSize; totalWordIter++){
	if(!strcmp(inStrWords_p->at(wordIter).c_str(), totalWords_p->at(totalWordIter).c_str())){
	  wordPasses = true;
	  break;
	}
      }
      if(!wordPasses){
	doIter = false;
	break;
      }
    }
    if(doIter) newIter++;
    else newStr_p->erase(newStr_p->begin()+newIter);

    inStrWords_p->clear();
    delete inStrWords_p;
  }

  std::string tempOutName = outName;
  std::string repStr = "_MixedOutput.txt";
  if(tempOutName.find(".txt") != std::string::npos){
    tempOutName.replace(tempOutName.find(".txt"), 4, repStr);
  }
  tempOutName = outDirFull + tempOutName;
   
 
  std::string tempOutNameTweet = outName;
  std::string repStrTweet = "_TweetOutput.txt";
  if(tempOutNameTweet.find(".txt") != std::string::npos){
    tempOutNameTweet.replace(tempOutNameTweet.find(".txt"), 4, repStrTweet);
  }
  tempOutNameTweet = outDirTweet + tempOutNameTweet;

  std::srand(unsigned(std::time(NULL)));
  std::random_shuffle(newStr_p->begin(), newStr_p->end(), myrandom);

  const int newStrSize = (int)newStr_p->size();
 
  if(checkMakeDir(outDirFull)){
    std::ofstream outFile;

    if(doAppend) outFile.open(tempOutName.c_str(), std::ios_base::app);
    else outFile.open(tempOutName.c_str());
    for(int iter = 0; iter < newStrSize; iter++){
      outFile << newStr_p->at(iter) << std::endl;
    }
  
    outFile.close();
  }
  else{
    std::cout << "Error making dir \'" << outDirFull << "\'. File \'" << tempOutName << "\' not written." << std::endl;
  }

  if(checkMakeDir(outDirTweet)){
    std::ofstream outTweetFile;
    if(doAppend) outTweetFile.open(tempOutNameTweet.c_str(), std::ios_base::app);
    else outTweetFile.open(tempOutNameTweet.c_str());
    for(int iter = 0; iter < newStrSize; iter++){
      if(newStr_p->at(iter).size() < 140) outTweetFile << newStr_p->at(iter) << std::endl;
    }

    outTweetFile.close();
  }
  else{
    std::cout << "Error making dir \'" << outDirTweet << "\'. File \'" << tempOutNameTweet << "\' not written." << std::endl;
  }
  
  totalWords_p->clear();
  delete totalWords_p;
  
  newStr_p->clear();
  delete newStr_p;

  inStr1_p->clear();
  delete inStr1_p;

  inStr2_p->clear();
  delete inStr2_p;

  return 0;
}

int runCreateNewIdioms(const std::string inFileName, const std::string inFileName2)
{
  std::string outName;

  std::string tempInFileName = inFileName;
  std::string tempInFileName2 = inFileName2;

  while(tempInFileName.find("/") != std::string::npos){
    tempInFileName.replace(0, tempInFileName.find("/")+1, "");
  }

  while(tempInFileName2.find("/") != std::string::npos){
    tempInFileName2.replace(0, tempInFileName2.find("/")+1, "");
  }

  int lead = -1;
  int pos = 0;
  while(lead == -1 && pos < tempInFileName.size() && pos <  tempInFileName2.size()){
    std::string tempChar1 = tempInFileName.substr(pos, 1);
    std::string tempChar2 = tempInFileName2.substr(pos, 1);

    if(!strcmp(tempChar1.c_str(), ".")) lead = 0;
    else if(!strcmp(tempChar2.c_str(), ".")) lead = 1;
    
    if(lead != -1) break;

    if(alphabetSoup.find(tempChar1.c_str()) == std::string::npos){
      std::cout << "Non-alphanumeric char in inFileName1, \'" + tempInFileName + "\'. Return 1." << std::endl;
      return 1;
    }
    else if(alphabetSoup.find(tempChar2.c_str()) == std::string::npos){
      std::cout << "Non-alphanumeric char in inFileName2, \'" + tempInFileName2 + "\'. Return 1." << std::endl;
      return 1;
    }
  
    boost::algorithm::to_lower(tempChar1);
    boost::algorithm::to_lower(tempChar2);
    
    int tempPos1 = alphabetSoup.find(tempChar1.c_str());
    int tempPos2 = alphabetSoup.find(tempChar2.c_str());
    
    if(tempPos1 > tempPos2){
      lead = 1;
    }
    else if(tempPos2 > tempPos1){
      lead = 0;
    }
    
    pos++;
  }
  
  if(lead != 0 && lead != 1){
    std::cout << "Sorting of file names failed. Return 1." << std::endl;
    return 1;
  }
  else if(lead == 0){
    if(tempInFileName.find(".txt") != std::string::npos) tempInFileName.replace(tempInFileName.find(".txt"), 4, "");
    outName = tempInFileName + "_" + tempInFileName2;
  }
  else if(lead == 1){
    if(tempInFileName2.find(".txt") != std::string::npos) tempInFileName2.replace(tempInFileName2.find(".txt"), 4, "");
    outName = tempInFileName2 + "_" + tempInFileName;
  }

  int retVal = createNewIdioms(inFileName, inFileName2, outName, false);
  retVal = createNewIdioms(inFileName2, inFileName, outName, true);

  return retVal;
}

int main(int argc, char *argv[])
{
  if(argc != 3){
    std::cout << "Usage: createNewIdioms.exe <inputFile> <inputFile2>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int result = runCreateNewIdioms(argv[1], argv[2]);

  return result;
}
