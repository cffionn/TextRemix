#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <algorithm> 
#include <cstdlib>
#include <ctime>

#include <boost/algorithm/string.hpp>

#include "include/globalDoDebug.h"
#include "include/defAlphaNumSoup.h"
#include "include/checkMakeDir.h"

const std::string outDirFull = "outputFull/";
const std::string outDirTweet = "outputTweet/";

int myrandom(int i){return std::rand()%i;}


bool isStringInVect(std::string inStr, std::vector<std::string>* inVect_p)
{
  bool isInVect = false;

  const int vectSize = (int)inVect_p->size();

  for(int iter = 0; iter < vectSize; iter++){
    if(inVect_p->at(iter).size() == inStr.size() && inVect_p->at(iter).find(inStr) != std::string::npos){
      isInVect = true;
      break;
    }
  }

  return isInVect;
}

std::vector<std::string> createNewIdioms(const std::string inFileName, const std::string inFileName2, const int numberOutputLines = -1)
{
  std::vector<std::string> returnVectorOfStrings;

  std::ifstream file;
  std::string str; 

  std::vector<std::string>* inStr1_p = new std::vector<std::string>;
  std::vector<std::string>* inStr2_p = new std::vector<std::string>;
  std::vector<std::string>* totalWords_p = new std::vector<std::string>;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;


  if(inFileName.find(".txt") != std::string::npos){
    file.open(inFileName.c_str());
    while(std::getline(file, str)){
      while(str.substr(0, 1).find(" ") != std::string::npos){
	str.replace(0, 1, "");
      }

      if(str.find("\r") != std::string::npos) str = str.substr(0, str.find("\r"));

      inStr1_p->push_back(str);
    }
    file.close();
  }
  else{
    std::cout << "inFileName 1, \'" << inFileName << "\' is invalid. Not \'.txt\'. return empty vector." << std::endl;
    return returnVectorOfStrings;
  }

  if(inFileName2.find(".txt") != std::string::npos){
    file.open(inFileName2.c_str());
    while(std::getline(file, str)){
      while(str.substr(0, 1).find(" ") != std::string::npos){
	str.replace(0, 1, "");
      }

      if(str.find("\r") != std::string::npos) str = str.substr(0, str.find("\r"));

      inStr2_p->push_back(str);
    }
    file.close();
  }
  else{
    std::cout << "inFileName 2, \'" << inFileName2 << "\' is invalid. Not \'.txt\'. return empty vector." << std::endl;
    return returnVectorOfStrings;
  }

  if(inStr1_p->size() == 0){
    std::cout << "Input file 1 empty. return empty vector" << std::endl;
    return returnVectorOfStrings;
  }

  if(inStr2_p->size() == 0){
    std::cout << "Input file 2 empty. return empty vector" << std::endl;
    return returnVectorOfStrings;
  }

  std::srand(unsigned(std::time(NULL)));
  std::random_shuffle(inStr1_p->begin(), inStr1_p->end(), myrandom);
  std::random_shuffle(inStr2_p->begin(), inStr2_p->end(), myrandom);


  std::vector<std::string>* newStr_p = new std::vector<std::string>;
  bool breakBool = false;

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

    for(int iter2 = 0; iter2 < inStr2Size; iter2++){
      for(int wordIter = 0; wordIter < str1WordsSize; wordIter++){
	if(inStr2_p->at(iter2).find(inStr1Words_p->at(wordIter)) != std::string::npos){
	  std::size_t pos1 = inStr1_p->at(iter).find(inStr1Words_p->at(wordIter).c_str());
	  std::size_t pos2 = inStr2_p->at(iter2).find(inStr1Words_p->at(wordIter).c_str());

	  std::string newStr = inStr1_p->at(iter).substr(0, pos1) + inStr2_p->at(iter2).substr(pos2, inStr2_p->size() - pos2);
	  bool isUsedStr = isStringInVect(newStr, newStr_p);
	  if(!isUsedStr) isUsedStr = isStringInVect(newStr, inStr1_p);
	  if(!isUsedStr) isUsedStr = isStringInVect(newStr, inStr2_p);
	  if(!isUsedStr) isUsedStr = isStringInVect(newStr, totalWords_p);

	  if(!isUsedStr){
	    std::vector<std::string>* wordsInNewStr_p = new std::vector<std::string>;
	    std::string tempNewStr = newStr;

	    while(true){
	      std::size_t tempPos = tempNewStr.find(" ");
	      if(tempPos == std::string::npos){
		wordsInNewStr_p->push_back(tempNewStr);
		break;
	      }
	      wordsInNewStr_p->push_back(tempNewStr.substr(0, tempPos+1));
	      tempNewStr = tempNewStr.substr(tempPos+1, tempNewStr.size()-tempPos+1);
	    }

	    bool strIsGood = true;
	    for(int newWordIter = 0; newWordIter < (int)wordsInNewStr_p->size(); newWordIter++){
	      bool wordIsGood = false;
	      std::string newWord = wordsInNewStr_p->at(newWordIter);

	      for(int totWordIter = 0; totWordIter < (int)totalWords_p->size(); totWordIter++){
		std::string totWord = totalWords_p->at(totWordIter);
		
		if(newWord.size() == totWord.size() && newWord.find(totWord) != std::string::npos){
		  wordIsGood = true;
		  break;
		}
	      }

	      if(!wordIsGood){
		strIsGood = false;
		break;
	      }
	    }

	    if(!strIsGood) isUsedStr = true;
	    
	    wordsInNewStr_p->clear();
	    delete wordsInNewStr_p;
	  }

	  if(!isUsedStr) newStr_p->push_back(newStr);

	  if((int)newStr_p->size() >= numberOutputLines && numberOutputLines > 0){
	    breakBool = true;
	    break;
	  }
	}
      }
      if(breakBool) break;
    }

    if(breakBool) break;

    inStr1Words_p->clear();
    delete inStr1Words_p;
  }

  const int numberOfStrings = newStr_p->size();
  returnVectorOfStrings.reserve(numberOfStrings);

  for(int iter = 0; iter < numberOfStrings; iter++){
    returnVectorOfStrings.push_back(newStr_p->at(iter));
  }

  totalWords_p->clear();
  delete totalWords_p;
  
  newStr_p->clear();
  delete newStr_p;

  inStr1_p->clear();
  delete inStr1_p;

  inStr2_p->clear();
  delete inStr2_p;

  return returnVectorOfStrings;
}

int runCreateNewIdioms(const std::string inFileName, const std::string inFileName2, int numberOutputLines)
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
  while(lead == -1 && pos < (int)tempInFileName.size() && pos <  (int)tempInFileName2.size()){
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

  bool sameFile = (inFileName.size() == inFileName2.size() && inFileName.find(inFileName2) != std::string::npos);

  std::vector<std::string> newStrVect1;
  if(numberOutputLines > 0) newStrVect1.reserve(numberOutputLines);
  newStrVect1 = createNewIdioms(inFileName, inFileName2, numberOutputLines);

  std::vector<std::string> newStrVect2;
  if(numberOutputLines > 0) newStrVect2.reserve(numberOutputLines);
  if(!sameFile) newStrVect2 = createNewIdioms(inFileName2, inFileName, numberOutputLines);

  std::cout << newStrVect1.size() << ", " << newStrVect2.size() << std::endl;

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

  std::random_shuffle(newStrVect1.begin(), newStrVect1.end(), myrandom);
  std::random_shuffle(newStrVect2.begin(), newStrVect2.end(), myrandom);

  if(checkMakeDir(outDirFull)){
    std::ofstream outFile(tempOutName.c_str(), std::ofstream::out | std::ofstream::trunc);
    outFile.close();

    outFile.open(tempOutName.c_str(), std::ios_base::app);

    int vectIter = 0;
    int writeIter = 0;
    while((vectIter < (int)newStrVect1.size() || vectIter < (int)newStrVect2.size()) && writeIter < numberOutputLines){
      
      if(vectIter < (int)newStrVect1.size()){
	outFile << newStrVect1.at(vectIter) << std::endl;

	writeIter++;
      }
      
      if(vectIter < (int)newStrVect2.size() && writeIter < numberOutputLines){
	outFile << newStrVect2.at(vectIter) << std::endl;

        writeIter++;
      }
      
      vectIter++;
    }
  
    outFile.close();
  }
  else{
    std::cout << "Error making dir \'" << outDirFull << "\'. File \'" << tempOutName << "\' not written." << std::endl;
  }

  if(checkMakeDir(outDirTweet)){
    std::ofstream outFileTweet(tempOutNameTweet.c_str(), std::ofstream::out | std::ofstream::trunc);
    outFileTweet.close();

    outFileTweet.open(tempOutNameTweet.c_str(), std::ios_base::app);

    int vectIter = 0;
    int writeIter = 0;
    while((vectIter < (int)newStrVect1.size() || vectIter < (int)newStrVect2.size()) && writeIter < numberOutputLines){
      if(vectIter < (int)newStrVect1.size()){

	if((int)newStrVect1.at(vectIter).size() <= 140){
	  outFileTweet << newStrVect1.at(vectIter) << std::endl;
	  writeIter++;
	}
      }

      if(vectIter < (int)newStrVect2.size() && writeIter < numberOutputLines){

	if((int)newStrVect2.at(vectIter).size() <= 140){
	  outFileTweet << newStrVect2.at(vectIter) << std::endl;
	  writeIter++;
	}
      }

      vectIter++;
    }    

    outFileTweet.close();
  }
  else{
    std::cout << "Error making dir \'" << outDirTweet << "\'. File \'" << tempOutNameTweet << "\' not written." << std::endl;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 4){
    std::cout << "Usage: createNewIdioms.exe <inputFile> <inputFile2> <numberOfOutputLines, -1 if max>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  std::string arg3 = argv[3];
  if(arg3.size() > 1 && arg3.substr(0,1).find("-") != std::string::npos) arg3 = arg3.substr(1, arg3.size()-1);

  if(!isAllNumber(arg3)){
    std::cout << "Arg 3 \'" << arg3 << "\' is not a number. Please give number of desired output lines (-1 if max)" << std::endl;
  }

  int result = runCreateNewIdioms(argv[1], argv[2], std::stoi(argv[3]));

  return result;
}
