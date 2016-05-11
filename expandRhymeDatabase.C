#include <iostream>
#include <fstream>
#include <vector>

#include "interface/globalDoDebug.h"
#include "interface/getRhyme.h"
#include "interface/checkMakeDir.h"
#include "interface/returnFileList.h"
#include "interface/parseYesNo.h"

#include <boost/algorithm/string.hpp>

int expandRhymeDatabase()
{
  //  const bool doInteractive = true;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  if(!checkDir(rhymeDatabasePath)){
    std::cout << "rhymeDatabasePath, \'" << rhymeDatabasePath << "\' not a directory. Return 1." << std::endl;
    return 1;
  }

  std::vector<std::string> rhymeFileList = returnFileList(rhymeDatabasePath, ".txt");
  
  if(rhymeFileList.size() == 0){
    std::cout << "rhymeDatabasePath, \'" << rhymeDatabasePath << "\' contains no files with filter .txt. Return 1." << std::endl;
    return 1;
  }

  if(-1 == orderRhymeFileList(&rhymeFileList)) return 1;

  std::ifstream noRhymeFile(rhymeFileList.at(rhymeFileList.size()-1).c_str());
  std::string wordStr;
  std::vector<std::string>* wordStrVect_p = new std::vector<std::string>;
  std::vector<std::string>* stillNoRhymeVect_p = new std::vector<std::string>;

  while(std::getline(noRhymeFile, wordStr)){
    if(wordStr.size() == 0) continue;
    wordStrVect_p->push_back(wordStr);
  }


  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  if(wordStrVect_p->size() == 0){
    std::cout << "Input file is empty. Return 1." << std::endl;
    return 1;
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  const int nMaxBackStr = 3;
  int wordIter = 0;
  while(wordStrVect_p->size() > wordIter){
    std::string wordLastStr = wordStrVect_p->at(wordIter);
    
    while(wordLastStr.size() > nMaxBackStr){
      wordLastStr.replace(0, 1, "");
    }

    std::vector<std::string>* isRhymeStrVect_p = new std::vector<std::string>;
    
    for(int rhymeIter = wordIter+1; rhymeIter < (int)wordStrVect_p->size(); rhymeIter++){
      std::string rhymeWordStr = wordStrVect_p->at(rhymeIter);
      std::string rhymeWordCutStr = wordStrVect_p->at(rhymeIter);


      while(rhymeWordCutStr.size() > nMaxBackStr){
	rhymeWordCutStr.replace(0, 1, "");
      }

      if(rhymeWordCutStr.find(wordLastStr) != std::string::npos){
	isRhymeStrVect_p->push_back(rhymeWordStr);
	continue;
      }
      else if(wordLastStr.find(rhymeWordCutStr) != std::string::npos){
	isRhymeStrVect_p->push_back(rhymeWordStr);
	continue;
      }
      else if(rhymeWordCutStr.size() == nMaxBackStr){
	if(wordLastStr.find(rhymeWordCutStr.substr(1, nMaxBackStr-1)) != std::string::npos){
	  isRhymeStrVect_p->push_back(rhymeWordStr);
	}
      }
      else if(wordLastStr.size() == nMaxBackStr){
	if(rhymeWordCutStr.find(wordLastStr.substr(1, nMaxBackStr-1)) != std::string::npos){
          isRhymeStrVect_p->push_back(rhymeWordStr);
        }
      }
    }

    std::cout << "Word \'" << wordStrVect_p->at(wordIter) << "\'. Possible rhymes: " << std::endl;

    for(int rhymeIter = 0; rhymeIter < (int)isRhymeStrVect_p->size(); rhymeIter++){
      std::cout << " " << isRhymeStrVect_p->at(rhymeIter) << std::endl;
    }

    std::cout << "Create new rhyme file for word \'" << wordStrVect_p->at(wordIter) << "\'? (y/n) ";
    std::string input;
    std::cin >> input;
    
    int yesNo = parseYesNo(input);

    if(yesNo == -1) continue;
    else if(yesNo == 1){
      //yes block
      std::string newFileName = wordStrVect_p->at(wordIter).substr(0, 1);
      boost::algorithm::to_upper(newFileName);
      if(wordStrVect_p->at(wordIter).size() > 1) newFileName = newFileName + wordStrVect_p->at(wordIter).substr(1, wordStrVect_p->at(wordIter).size()-1);
      newFileName = wordLastStr + "_" + newFileName + ".txt";
      int yesNo2 = -1;
      while(yesNo2 == -1 || yesNo2 == 0){
	if(yesNo2 == -1){
	  std::cout << "Filename \'" << newFileName << "\' ok? (y/n)";
	  std::cin >> input;
	  yesNo2 = parseYesNo(input);
	}
	else{
	  std::cout << "Please input newFileName: ";
	  std::string inputFileName;
	  std::cin >> inputFileName;

	  if(inputFileName.substr(inputFileName.size()-4, 4).find(".txt") != std::string::npos){
	    newFileName = inputFileName;
	  }
	  else{
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. Please end in \'.txt\'" << std::endl;
	  }
	}
      }
    }
    else if(yesNo == 0){
      //no block
      stillNoRhymeVect_p->push_back(wordStrVect_p->at(wordIter));      
    }
    else{
      std::cout << "isYesNo returning non-0, 1, -1. Debug." << std::endl;
      continue;
    }

    isRhymeStrVect_p->clear();
    delete isRhymeStrVect_p;

    wordIter++;
  }

  stillNoRhymeVect_p->clear();
  delete stillNoRhymeVect_p;
  
  wordStrVect_p->clear();
  delete wordStrVect_p;

  return 0;
}

int main()
{
  int retVal;

  retVal = expandRhymeDatabase();

  return retVal;
}
