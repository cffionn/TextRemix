#include <iostream>
#include <fstream>
#include <vector>

#include "include/globalDoDebug.h"
#include "include/getRhyme.h"
#include "include/checkMakeDir.h"
#include "include/returnFileList.h"
#include "include/defAlphaNumSoup.h"
#include "include/parseYesNo.h"

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
  while((int)wordStrVect_p->size() > wordIter){
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

	  if(inputFileName.size () < 4){
	    std::cout << "Filename \'" << inputFileName << "\' too short. Please try new name." << std::endl;
	    continue;
	  }
	  else if(inputFileName.substr(inputFileName.size()-4, 4).find(".txt") == std::string::npos){
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. Please end in \'.txt\'" << std::endl;
	    continue;
	  }
	  else if(inputFileName.find("_") == std::string::npos){
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. Please use \'_\' as part of valid form \'<sound>_<word>.txt\'" << std::endl;
	    continue;
	  }

	  std::string inputFileNameSoundStr = inputFileName.substr(0, inputFileName.find("_"));
	  std::string inputFileNameWordStr = inputFileName.substr(inputFileName.find("_")+1, inputFileName.find(".") - inputFileName.find("_") - 1);

	  if(inputFileNameSoundStr.size() > 3 || inputFileNameSoundStr.size() == 0){
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. Please use 1-3 letters in <sound> as part of valid form \'<sound>_<word>.txt\'" << std::endl;
	    continue;
	  }
	  else if(!containsVowel(inputFileNameSoundStr)){
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. <sound> must contain vowel as part of valid form \'<sound>_<word>.txt\'" << std::endl;
	    continue;
	  }
	  else if(containsNotAlphabet(inputFileNameSoundStr)){
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. <sound>, \'" << inputFileNameSoundStr << "\' must be alphabet as part of valid form \'<sound>_<word>.txt\'" << std::endl;
	    continue;
	  }
	  else if(containsNotAlphabet(inputFileNameWordStr)){
	    std::cout << "Input filename \'" << inputFileName << "\' is invalid. <word>, \'" << inputFileNameWordStr << "\' must be alphabet as part of valid form \'<sound>_<word>.txt\'" << std::endl;
	    continue;
	  }
	  else{
	    bool wordValid = false;
	    if(wordStrVect_p->at(wordIter).find(inputFileNameWordStr) != std::string::npos && wordStrVect_p->at(wordIter).size() == inputFileNameWordStr.size()) wordValid = true;

	    for(int rhymeIter = 0; rhymeIter < (int)isRhymeStrVect_p->size(); rhymeIter++){
	      if(isRhymeStrVect_p->at(rhymeIter).find(inputFileNameWordStr) != std::string::npos && inputFileNameWordStr.size() == isRhymeStrVect_p->at(rhymeIter).size()){
		wordValid = true;
		break;
	      }
	    }

	    if(!wordValid){
	      std::cout << "Input fileName \'" << inputFileName << "\' is invalid. <word>, \'" << inputFileNameWordStr << "\' must be of the following list as part of valid form \'<sound>_<word>.txt\'" << std::endl;
	      
	      std::cout << " Possible words: \'" << wordStrVect_p->at(wordIter) << "\', ";
	      for(int rhymeIter = 0; rhymeIter < (int)isRhymeStrVect_p->size(); rhymeIter++){
		if(rhymeIter < (int)isRhymeStrVect_p->size() - 1) std::cout << "\'" << isRhymeStrVect_p->at(rhymeIter) << "\', ";
		else std::cout << "\'" << isRhymeStrVect_p->at(rhymeIter) << "\'." << std::endl;
	      }

	      continue;
	    }
	  }

	  std::string tempStartWordStr = inputFileNameWordStr.substr(0,1);
	  boost::algorithm::to_upper(tempStartWordStr);
	  std::string tempEndWordStr = "";
	  if(inputFileNameWordStr.size() > 1) tempEndWordStr = inputFileNameWordStr.substr(1, inputFileNameWordStr.size()-1);

	  inputFileName = inputFileNameSoundStr + "_" + tempStartWordStr + tempEndWordStr + ".txt";

	  newFileName = inputFileName;
	  yesNo2 = -1;	  
	}
      }
    
      newFileName = rhymeDatabasePath + newFileName;
      std::ofstream newRhymeFile(newFileName.c_str());
      newRhymeFile << wordStrVect_p->at(wordIter) << std::endl;
      
      std::cout << "File \'" << newFileName << "\' created. Word \'" << wordStrVect_p->at(wordIter) << "\' added." << std::endl;

      int rhymeWordPos = 0;
      while((int)isRhymeStrVect_p->size() > rhymeWordPos){
	std::cout << "Add word \'" << isRhymeStrVect_p->at(rhymeWordPos) << "\' to file \'" << newFileName << "\'? (y/n)";
	std::cin >> input;
	int inputVal = parseYesNo(input);
	if(inputVal == -1) continue;
	else if(inputVal == 1){
	  newRhymeFile << isRhymeStrVect_p->at(rhymeWordPos) << std::endl;
	  //edit here

	  for(int wordIter2 = wordIter+1; wordIter2 < (int)wordStrVect_p->size(); wordIter2++){
	    if(wordStrVect_p->at(wordIter2).size() == isRhymeStrVect_p->at(rhymeWordPos).size() && wordStrVect_p->at(wordIter2).find(isRhymeStrVect_p->at(rhymeWordPos)) != std::string::npos){
	      wordStrVect_p->erase(wordStrVect_p->begin()+wordIter2);
	      break;
	    }
	  }
	}
	
	rhymeWordPos++;
      }
      
      newRhymeFile.close(); 
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
