#include <fstream>
#include <iostream>
#include <string>

#include "interface/getSyllable.h"
#include "interface/checkMakeDir.h"
#include "interface/returnFileList.h"
#include "interface/defAlphaNumSoup.h"

#include <boost/algorithm/string.hpp>

const std::string underscoreStr = "_";

int sortFileStrings(const std::string inFileName)
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
  
  const int nStr = (int)strForSort_p->size();
  
  if(nStr == 0){
    std::cout << "Input file is empty. Return 1." << std::endl;
    return 1;
  }

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

  std::string newFileName = inFileName;
  std::string newFilePath = "";

  if(newFileName.find("noRhyme") == std::string::npos){
    while(newFileName.find("/") != std::string::npos){
      newFilePath = newFilePath + newFileName.substr(0, newFileName.find("/")+1);
      newFileName.replace(0, newFileName.find("/")+1, "");
    }
    
    while(newFileName.find(".txt") != std::string::npos){
      newFileName.replace(newFileName.find(".txt"), 4, "");
    }
    
    int newFileNameSize = (int)newFileName.size();
    
    for(int fileNameIter = 0; fileNameIter < newFileNameSize; fileNameIter++){
      if(alphabetSoupUpper.find(newFileName.at(fileNameIter)) != std::string::npos || underscoreStr.find(newFileName.at(fileNameIter)) != std::string::npos){
	newFileName.replace(fileNameIter, newFileName.size()-fileNameIter, "");
	break;
      }
    }

    std::string firstConsonantWord = "";
    for(int strIter = 0; strIter < nStr; strIter++){
      if(alphabetSoupConsonant.find(strForSort_p->at(strIter).at(0)) != std::string::npos){
	firstConsonantWord = strForSort_p->at(strIter);
	break;
      } 
    }
    if(firstConsonantWord.size() == 0) firstConsonantWord = strForSort_p->at(0);

    std::string firstConsonantWordLetter = firstConsonantWord.substr(0, 1);
    boost::algorithm::to_upper(firstConsonantWordLetter);
    
    firstConsonantWord = firstConsonantWordLetter + firstConsonantWord.substr(1, firstConsonantWord.size()-1);
  
    newFileName = newFilePath + newFileName + "_" + firstConsonantWord + ".txt";
  }

  if(std::remove(inFileName.c_str()) != 0){
    std::cout << "Error deleting file \'" << inFileName << "\'. Return 1" << std::endl;
    return 1;
  }

  std::ofstream newFile(newFileName);
  for(int strIter = 0; strIter < nStr; strIter++){
    newFile << strForSort_p->at(strIter) << std::endl;
  }
  newFile.close();
  
  strSylForSort_p->clear();
  delete strSylForSort_p;
  
  strForSort_p->clear();
  delete strForSort_p;

  return 0;
}


int sortDatabaseStrings(const std::string inPath)
{
  int retVal = -1;

  if(!checkDir(inPath)){
    std::cout << "Invalid path \'" << inPath << "\' given. Return 1." << std::endl;
    return 1;
  }
  else if(inPath.find("Database") == std::string::npos){
    std::cout << "Input path \'" << inPath << "\' not a database. Return 1." << std::endl;
    return 1;
  }

  const std::string filterString = ".txt";
  
  std::vector<std::string> dbFileList = returnFileList(inPath, filterString);
  int nFiles = (int)dbFileList.size();

  for(int fileIter = 0; fileIter < nFiles; fileIter++){
    retVal = sortFileStrings(dbFileList.at(fileIter));
    if(retVal != 0) break;
  }

  return retVal;
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

