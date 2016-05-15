#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"
#include "include/returnFileList.h"
#include "include/parseYesNo.h"

#include <boost/algorithm/string.hpp>

int removeDatabaseDuplicates(const std::string dirPath)
{
  int retVal = -1;

  if(!checkDir(dirPath)){
    std::cout << "Invalid path \'" << dirPath << "\' given. Return 1." << std::endl;
    return 1;
  }
  else if(dirPath.find("Database") == std::string::npos){
    std::cout << "Input path \'" << dirPath << "\' not a database. Return 1." << std::endl;
    return 1;
  }
  else if(dirPath.find("input") != std::string::npos){
    std::cout << "Input path \'" << dirPath << "\' not a valid database. Cannot be \'input\'. Return 1." << std::endl;
    return 1;
  }

  const std::string filterString = ".txt";
  std::vector<std::string> dbFileList = returnFileList(dirPath, filterString);
  const int nFiles = (int)dbFileList.size();

  for(int fileIter = 0; fileIter < nFiles; fileIter++){
    std::ifstream file1(dbFileList.at(fileIter));
    std::string inStr1;
    std::vector<std::string>* inStrVect1_p = new std::vector<std::string>;

    while(std::getline(file1, inStr1)){
      if(inStr1.size() == 0) continue;
      inStrVect1_p->push_back(inStr1);
    }
    file1.close();

    for(int fileIter2 = fileIter+1; fileIter2 < nFiles; fileIter2++){
      std::ifstream file2(dbFileList.at(fileIter2));
      std::string inStr2;
      std::vector<std::string>* inStrVect2_p = new std::vector<std::string>;

      while(std::getline(file2, inStr2)){
	if(inStr2.size() == 0) continue;
	inStrVect2_p->push_back(inStr2);
      }      
      file2.close();

      int wordIter1 = 0;
      while(wordIter1 < (int)inStrVect1_p->size()){
	std::string word1 = inStrVect1_p->at(wordIter1);

	int wordIter2 = 0;
	while(wordIter2 < (int)inStrVect2_p->size()){
	  std::string word2 = inStrVect2_p->at(wordIter2); 
	  
	  if(word1.size() == word2.size() && word1.find(word2) != std::string::npos){
	    std::cout << "Duplicate word \'" << word1 << "\' in files \'" << dbFileList.at(fileIter) << "\', \'" << dbFileList.at(fileIter2) << "\'." << std::endl;

	    
	    int inputInt = -1;
	    while(inputInt == -1){
	      std::cout << " Remove word \'" << word1 << "\' from file \'" << dbFileList.at(fileIter) << "\'? (y/n)";
	      std::string input;
	      std::cin >> input;

	      inputInt = parseYesNo(input);

	      if(inputInt == 1){
		std::cout << "YES!" << std::endl;
	      }
	      else if(inputInt == 0){
		std::cout << "No?" << std::endl;
	      }
	    }

	  }
	  else wordIter2++;
	}

	wordIter1++;
      }

      inStrVect2_p->clear();
      delete inStrVect2_p;
    }    

    inStrVect1_p->clear();
    delete inStrVect1_p;
  }
  

  retVal = 0;
  return retVal;
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: removeDatabaseDuplicates.exe <inPath>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = removeDatabaseDuplicates(argv[1]);
  return retVal;
}
