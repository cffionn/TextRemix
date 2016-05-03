#include <fstream>
#include <iostream>
#include <string>

#include "interface/getSyllable.h"
#include "interface/checkMakeDir.h"
#include "interface/returnFileList.h"
#include "interface/defAlphaNumSoup.h"

int sortDatabaseStrings(const std::string inPath)
{
  std::vector<std::string> dbFileList = returnFileList(inPath, ".txt");
  
  int nFiles = (int)dbFileList.size();

  for(int fileIter = 0; fileIter < nFiles; fileIter++){
    std::ifstream file(dbFileList.at(fileIter).c_str());
    std::string str;
    std::vector<std::string>* strForSort_p = new std::vector<std::string>;

    while(std::getline(file, str)){
      strForSort_p->push_back(str);
    }

    int nStr = (int)strForSort_p->size();

    for(int strIter = 0; strIter < nStr-1; strIter++){
      std::string tempStr = strForSort_p->at(strIter);
      int nChar = (int)tempStr.size();
      
      for(int charIter = 0; charIter < nChar; charIter++){
	if(alphabetSoup.find(tempStr.at(charIter)) == std::string::npos){
	  std::cout << "Word \'" << tempStr << "\' in file \'" << dbFileList.at(fileIter) << "\' has none alphabet char. Please remove and try again. Return 1." << std::endl;
	  return 1;
	}
      }
    }

    strForSort_p->clear();
    delete strForSort_p;
  }

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

