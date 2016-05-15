#include <fstream>
#include <iostream>
#include <string>

#include "include/globalDoDebug.h"
#include "include/getSyllable.h"
#include "include/getRhyme.h"
#include "include/checkMakeDir.h"
#include "include/returnFileList.h"
#include "include/defAlphaNumSoup.h"

#include <boost/algorithm/string.hpp>

const std::string outSylPath = "outputSylSort/";

int createSyllableSorted(const std::string inFileName, const bool doInteractiveRhyme)
{
  std::vector<std::string>* inStr_p = new std::vector<std::string>;
  std::vector<std::string>* lastWordStr_p = new std::vector<std::string>;
  std::vector<std::string>* lastWordRhymeStr_p = new std::vector<std::string>;
  std::vector<int>* inStrSyl_p = new std::vector<int>;
  std::string str;

  std::vector<std::string> rhymeFileList = returnFileList(rhymeDatabasePath, ".txt");

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  int rhymeListPos = 0;
  while((int)rhymeFileList.size() > rhymeListPos){
    std::cout << rhymeFileList.at(rhymeListPos) << std::endl;
    if(rhymeFileList.at(rhymeListPos).size() - rhymeDatabasePath.size() < 4) rhymeFileList.erase(rhymeFileList.begin()+rhymeListPos);
    else if(rhymeFileList.at(rhymeListPos).substr(rhymeFileList.at(rhymeListPos).size()-4, 4).find(".txt") == std::string::npos) rhymeFileList.erase(rhymeFileList.begin()+rhymeListPos);
    else rhymeListPos++;
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  if(inFileName.find(".txt") == std::string::npos){
    std::cout << "inFileName, \'" << inFileName << "\' is invalid. Not \'.txt\'. Return 1." << std::endl;
    return 1;
  }

  std::ifstream file(inFileName);

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  int numberOfLines = 0;
  while(std::getline(file, str)){
    numberOfLines++;
  }

  int numberOfLines2 = std::max(10, numberOfLines);

  file.close();
  file.open(inFileName);

  int lineIter = 0;
  int fillIter = 1;

  while(std::getline(file, str)){
    if(str.size() == 0) continue;

    str = replaceNumbersWithWords(str);

    inStr_p->push_back(str);
    inStrSyl_p->push_back(getSyllables(str));

    while(!strcmp(str.substr(str.size()-1, 1).c_str(), " ")){
      str.replace(str.size()-1, 1, "");
    }

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

    while(str.find(" ") != std::string::npos){
      str.replace(0, str.find(" ")+1, "");
    }

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

    

    int iter = 0;
    while(iter < (int)str.size()){
      if(alphabetSoup.find(str[iter]) == std::string::npos) str.replace(iter, 1, "");
      else iter++;
    }

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

    boost::algorithm::to_lower(str);

    lastWordStr_p->push_back(str);

    int rhymePos = getRhyme(str, &rhymeFileList, doInteractiveRhyme);

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

    if(fillIter%10 == 0 || lineIter%(numberOfLines2/10) == 0){
      std::cout << "Line number " << lineIter << "/" << numberOfLines - 1 << std::endl;
      fillIter++;
    }

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;


    std::string rhymeStr = rhymeFileList.at(rhymePos).substr(rhymeFileList.at(rhymePos).find("/")+1, rhymeFileList.at(rhymePos).find("/")+1-rhymeFileList.at(rhymePos).size());
    rhymeStr = rhymeStr.substr(0, rhymeStr.find(".txt"));
    lastWordRhymeStr_p->push_back(rhymeStr);

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

    lineIter++;
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  if(inStr_p->size() == 0){
    std::cout << "Input file empty. Return 1." << std::endl;
    return 1;
  }

  for(int iter = 0; iter < (int)inStr_p->size()-1; iter++){
    for(int iter2 = iter+1; iter2 < (int)inStr_p->size(); iter2++){
      if(inStrSyl_p->at(iter) < inStrSyl_p->at(iter2)){

	int tempSyl = inStrSyl_p->at(iter);
	std::string tempStr = inStr_p->at(iter);
	std::string tempWordStr = lastWordStr_p->at(iter);
	std::string tempWordRhymeStr = lastWordRhymeStr_p->at(iter);

	inStrSyl_p->at(iter) = inStrSyl_p->at(iter2);
	inStr_p->at(iter) = inStr_p->at(iter2);
	lastWordStr_p->at(iter) = lastWordStr_p->at(iter2);
	lastWordRhymeStr_p->at(iter) = lastWordRhymeStr_p->at(iter2);

	inStrSyl_p->at(iter2) = tempSyl;
	inStr_p->at(iter2) = tempStr;
	lastWordStr_p->at(iter2) = tempWordStr;
	lastWordRhymeStr_p->at(iter2) = tempWordRhymeStr;
      }
    }
  }
  
  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  int subSortIter = 0;

  while(subSortIter < (int)(inStr_p->size())){
    int subSyl = inStrSyl_p->at(subSortIter);

    int subIterEnd = 1;
    while(subSortIter+subIterEnd < (int)inStr_p->size()){
      if(subSyl != inStrSyl_p->at(subSortIter+subIterEnd)) break;
      subIterEnd++;						     
    }

    for(int tempIter = subSortIter; tempIter < subSortIter+subIterEnd-1; tempIter++){
      for(int tempIter2 = tempIter+1; tempIter2 < subSortIter+subIterEnd; tempIter2++){
      
	std::string tempWord1 = lastWordStr_p->at(tempIter);
	std::string tempWord2 = lastWordStr_p->at(tempIter2);

	int lead = -1;
	int pos = 0;


	int tempPos1 = getRhyme(tempWord1, &rhymeFileList, doInteractiveRhyme);
	int tempPos2 = getRhyme(tempWord2, &rhymeFileList, doInteractiveRhyme);

	if(tempPos1 > tempPos2) lead = 1;
	else if(tempPos1 < tempPos2) lead = 0;
	else{
	  while(lead == -1 && pos < (int)tempWord1.size() && pos < (int)tempWord2.size()){
	    std::string tempChar1 = tempWord1.substr(pos, 1);
	    std::string tempChar2 = tempWord2.substr(pos, 1);
	    
	    tempPos1 = alphabetSoup.find(tempChar1.c_str());
	    tempPos2 = alphabetSoup.find(tempChar2.c_str());

	    if(tempPos1 > tempPos2) lead = 1;
	    else if(tempPos1 < tempPos2) lead = 0;
	    else if(pos+1 == (int)tempWord1.size()) lead = 0;
	    else if(pos+1 == (int)tempWord2.size()) lead = 1;  

	    pos++;
	  }
	}

	if(lead == 1){
	  int tempSyl1 = inStrSyl_p->at(tempIter);
	  std::string tempStr1 = inStr_p->at(tempIter);
	  std::string tempRhymeStr1 = lastWordRhymeStr_p->at(tempIter);

	  inStr_p->at(tempIter) = inStr_p->at(tempIter2);
	  inStrSyl_p->at(tempIter) = inStrSyl_p->at(tempIter2);
	  lastWordStr_p->at(tempIter) = lastWordStr_p->at(tempIter2);
	  lastWordRhymeStr_p->at(tempIter) = lastWordRhymeStr_p->at(tempIter2);

	  inStr_p->at(tempIter2) = tempStr1;
	  inStrSyl_p->at(tempIter2) = tempSyl1;
	  lastWordStr_p->at(tempIter2) = tempWord1;
	  lastWordRhymeStr_p->at(tempIter2) = tempRhymeStr1;
	}
      }
    }

    subSortIter += subIterEnd;
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  std::string tempInFileName = inFileName;
  while(tempInFileName.find("/") != std::string::npos){
    tempInFileName.replace(0, tempInFileName.find("/")+1, "");
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  std::string outName = tempInFileName;
  std::string repStr = "_SylSort.txt";
  if(outName.find(".txt") != std::string::npos){
    outName.replace(outName.find(".txt"), 4, repStr);
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;
  
  outName = outSylPath + outName;

  if(checkMakeDir(outSylPath)){
    std::ofstream outFile(outName.c_str());
    int sylNum = -1;
    for(int iter = 0; iter < (int)inStr_p->size(); iter++){
      if(inStrSyl_p->at(iter) != sylNum){
	sylNum = inStrSyl_p->at(iter);
	outFile << "Syllables: " << sylNum << std::endl;
      }
      outFile << "  " << inStr_p->at(iter) << " (" << inStrSyl_p->at(iter) << ", " << lastWordRhymeStr_p->at(iter)  << ")" << std::endl;
    }
    outFile.close();
  }
  else{
    std::cout << "Error making dir \'" << outSylPath << "\'. File \'" << outName << "\' not written." << std::endl;
  }

  inStrSyl_p->clear();
  delete inStrSyl_p;

  lastWordStr_p->clear();
  delete lastWordStr_p;

  lastWordRhymeStr_p->clear();
  delete lastWordRhymeStr_p;

  inStr_p->clear();
  delete inStr_p;

  return 0;
}


int main(int argc, char *argv[])
{
  if(argc != 3){
    std::cout << "Usage: createSyllableSorted.exe <inputFileName> <doInteractiveRhyme>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  const std::string arg1 = argv[1];
  const std::string arg2 = argv[2];

  if(arg2.size() != 1 || (arg2.find("0") == std::string::npos && arg2.find("1") == std::string::npos )){
    std::cout << "Usage: createSyllableSorted.exe <inputFileName> <doInteractiveRhyme>" << std::endl;
    std::cout << "Arg \'<doInteractiveRhyme>\' invalid. Please input 1/0 for true/false. Return -1." << std::endl;
    return -1;
  }


  int retVal = createSyllableSorted(arg1, std::stoi(arg2));
  return retVal;
}

