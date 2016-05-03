#include <fstream>
#include <iostream>
#include <string>

#include "interface/getSyllable.h"
#include "interface/checkMakeDir.h"
#include "interface/returnFileList.h"
#include "interface/defAlphaNumSoup.h"

#include <boost/algorithm/string.hpp>

int sortDatabaseStrings(const std::string inFileName)
{
  if(!checkFile(inFileName)){
    std::cout << "Input file \'" << inFileName << "\' is invalid. Return 1." << std::endl;
  }

  std::ifstream file(inFileName.c_str());
  std::string str;
  std::vector<std::string>* strForSort_p = new std::vector<std::string>;
  std::vector<int>* strSylForSort_p = new std::vector<int>;
  
  while(std::getline(file, str)){
    strForSort_p->push_back(str);
  }
  
  int nStr = (int)strForSort_p->size();
  
  for(int strIter = 0; strIter < nStr; strIter++){
    std::string tempStr = strForSort_p->at(strIter);
    int nChar = (int)tempStr.size();
    
    for(int charIter = 0; charIter < nChar; charIter++){
      if(alphabetSoup.find(tempStr.at(charIter)) == std::string::npos){
	std::cout << "Word \'" << tempStr << "\' in file \'" << inFileName << "\' has none alphabet char. Please remove and try again. Return 1." << std::endl;
	return 1;
      }
    }
    
    boost::algorithm::to_lower(tempStr);
    strForSort_p->at(strIter) = tempStr;
    strSylForSort_p->push_back(getSyllable(tempStr));
  }

  for(int strIter = 0; strIter < nStr-1; strIter++){
    for(int strIter2 = strIter+1; strIter2 < nStr; strIter2++){
      std::string tempStr1 = strForSort_p->at(strIter);
      int tempStrSyl1 = strSylForSort_p->at(strIter);
      
      std::string tempStr2 = strForSort_p->at(strIter2);
      int tempStrSyl2 = strSylForSort_p->at(strIter2);
      
      int lead = -1;
      
      if(tempStrSyl1 < tempStrSyl2){
	lead = 0;
      }
      else if(tempStrSyl1 > tempStrSyl2){
	lead = 1;
      }
      else{
	int pos = 0;
	while(lead == -1 && pos < tempStr1.size() && pos < tempStr2.size()){
	  int tempPos1 = alphabetSoup.find(tempStr1[pos]);
	  int tempPos2 = alphabetSoup.find(tempStr2[pos]);
	  
	  if(tempPos1 > tempPos2) lead = 1;
	  else if(tempPos1 < tempPos2) lead = 0;
	  else if(pos+1 == (int)tempStr1.size()) lead = 0;
	  else if(pos+1 == (int)tempStr2.size()) lead = 1;

	  pos++;
	}
      }

      if(lead == -1){
	std::cout << "Error in comparison of words \'" << tempStr1 << "\', and \'" << tempStr2 << "\'. Return 1." << std::endl;
	return 1;
      }
      
      if(lead == 1){
	strForSort_p->at(strIter) = tempStr2;
	strSylForSort_p->at(strIter) = tempStrSyl2;
	
	strForSort_p->at(strIter2) = tempStr1;
	strSylForSort_p->at(strIter2) = tempStrSyl1;
      }      
    }
  }
  
  strSylForSort_p->clear();
  delete strSylForSort_p;
  
  strForSort_p->clear();
  delete strForSort_p;

  return 0;
}


int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: sortDatabaseStrings.exe <inPath>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = sortDatabaseStrings(argv[1]);
  return retVal;
}

