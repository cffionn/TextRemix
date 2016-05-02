#include <fstream>
#include <iostream>
#include <string>

#include "interface/getSyllable.h"

#include "interface/checkMakeDir.h"

const std::string outSylPath = "outputSylSort/";

const bool doDebug = false;

int createSyllableSorted(const std::string inFileName)
{
  std::vector<std::string>* inStr_p = new std::vector<std::string>;
  std::vector<std::string>* lastWordStr_p = new std::vector<std::string>;
  std::vector<int>* inStrSyl_p = new std::vector<int>;
  std::string str;

  std::ifstream file(inFileName);

  if(doDebug) std::cout << __LINE__ << std::endl;

  while(std::getline(file, str)){
    inStr_p->push_back(str);
    inStrSyl_p->push_back(getSyllables(str));

    while(!strcmp(str.substr(str.size()-1, 1).c_str(), " ")){
      str.replace(str.size()-1, 1, "");
    }

    if(doDebug) std::cout << __LINE__ << std::endl;

    while(str.find(" ") != std::string::npos){
      str.replace(0, str.find(" ")+1, "");
    }

    if(doDebug) std::cout << __LINE__ << std::endl;

    int iter = 0;
    while(iter < str.size()){
      if(alphabetSoup.find(str[iter]) == std::string::npos) str.replace(iter, 1, "");
      else iter++;
    }

    if(doDebug) std::cout << __LINE__ << std::endl;

    boost::algorithm::to_lower(str);

    lastWordStr_p->push_back(str);
  }

  if(doDebug) std::cout << __LINE__ << std::endl;

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

	inStrSyl_p->at(iter) = inStrSyl_p->at(iter2);
	inStr_p->at(iter) = inStr_p->at(iter2);
	lastWordStr_p->at(iter) = lastWordStr_p->at(iter2);

	inStrSyl_p->at(iter2) = tempSyl;
	inStr_p->at(iter2) = tempStr;
	lastWordStr_p->at(iter2) = tempWordStr;
      }
    }
  }
  
  if(doDebug) std::cout << __LINE__ << std::endl;

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

	int pos = 0;
	int lead = -1;

	while(lead == -1 && pos < (int)tempWord1.size() && pos < (int)tempWord2.size()){
	  std::string tempChar1 = tempWord1.substr(pos, 1);
	  std::string tempChar2 = tempWord2.substr(pos, 1);

	  int tempPos1 = alphabetSoup.find(tempChar1.c_str());
	  int tempPos2 = alphabetSoup.find(tempChar2.c_str());

	  if(tempPos1 > tempPos2) lead = 1;
	  else if(tempPos1 < tempPos2) lead = 0;
	  else if(tempPos1+1 == (int)tempWord1.size()) lead = 0;
	  else if(tempPos2+1 == (int)tempWord2.size()) lead = 1;

	  pos++;
	}

	if(lead == 1){
	  int tempSyl1 = inStrSyl_p->at(tempIter);
	  std::string tempStr1 = inStr_p->at(tempIter);

	  inStr_p->at(tempIter) = inStr_p->at(tempIter2);
	  inStrSyl_p->at(tempIter) = inStrSyl_p->at(tempIter2);
	  lastWordStr_p->at(tempIter) = lastWordStr_p->at(tempIter2);

	  inStr_p->at(tempIter2) = tempStr1;
	  inStrSyl_p->at(tempIter2) = tempSyl1;
	  lastWordStr_p->at(tempIter2) = tempWord1;

	}
      }
    }

    subSortIter += subIterEnd;
  }

  if(doDebug) std::cout << __LINE__ << std::endl;

  std::string tempInFileName = inFileName;
  while(tempInFileName.find("/") != std::string::npos){
    tempInFileName.replace(0, tempInFileName.find("/")+1, "");
  }

  if(doDebug) std::cout << __LINE__ << std::endl;

  std::string outName = tempInFileName;
  std::string repStr = "_SylSort.txt";
  if(outName.find(".txt") != std::string::npos){
    outName.replace(outName.find(".txt"), 4, repStr);
  }

  if(doDebug) std::cout << __LINE__ << std::endl;
  
  outName = outSylPath + outName;

  if(checkMakeDir(outSylPath)){
    std::ofstream outFile(outName.c_str());
    int sylNum = -1;
    for(int iter = 0; iter < (int)inStr_p->size(); iter++){
      if(inStrSyl_p->at(iter) != sylNum){
	sylNum = inStrSyl_p->at(iter);
	outFile << "Syllables: " << sylNum << std::endl;
      }
      outFile << "  " << inStr_p->at(iter) << " (" << inStrSyl_p->at(iter) << ")" << std::endl;
    }
    outFile.close();
  }
  else{
    std::cout << "Error making dir \'" << outSylPath << "\'. File \'" << outName << "\' not written." << std::endl;
  }

  inStrSyl_p->clear();
  delete inStrSyl_p;

  inStr_p->clear();
  delete inStr_p;

  return 0;
}


int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: createSyllableSorted.exe <inputFileName>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = createSyllableSorted(argv[1]);
  return retVal;
}

