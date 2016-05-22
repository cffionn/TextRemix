#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"
#include "include/checkOutputTxtFile.h"
#include "include/parseYesNo.h"

const std::string macDBDirStr = "machineDatabase/";
const std::string goodFileName = "goodStrings.txt";
const std::string badFileName = "badStrings.txt";

int addToMachineDatabase(const std::string inFileName)
{
  if(!checkOutputTxtFile(inFileName)) return -1;

  std::string tempGoodFileName = macDBDirStr+goodFileName;
  std::string tempBadFileName = macDBDirStr+badFileName;

  std::vector<std::string>* prevStr_p = new std::vector<std::string>;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  if(checkFile(tempGoodFileName)){
    std::ifstream prevFile(tempGoodFileName);
    std::string str;

    while(std::getline(prevFile, str)){
      prevStr_p->push_back(str);
    }

    prevFile.close();

    prevFile.open(tempBadFileName);
    while(std::getline(prevFile, str)){
      prevStr_p->push_back(str);
    }
    
    prevFile.close();
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  std::ifstream inFile(inFileName);
  std::string str;
  std::vector<std::string>* strVect_p = new std::vector<std::string>;

  while(std::getline(inFile, str)){
    bool continueBool = false;
    
    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

    for(int iter = 0; iter < (int)prevStr_p->size(); iter++){
      if(str.size() == prevStr_p->at(iter).size() && str.find(prevStr_p->at(iter)) != std::string::npos){
	continueBool = true;
	break;
      }
    }

    if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;


    if(continueBool) continue;

    strVect_p->push_back(str);
  }
  inFile.close();

  prevStr_p->clear();
  delete prevStr_p;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;


  const int nStr = (int)strVect_p->size();
  
  for(int iter = 0; iter < nStr; iter++){
    int yesNo = -1;
    std::string inStr = strVect_p->at(iter);

    while(yesNo == -1){
      std::cout << "\'" << inStr << "\'" << std::endl;
      std::cout << "  Is string good? (y/n): ";
      
      std::string input;
      std::cin >> input;

      yesNo = parseYesNo(input);

      if(yesNo == 1){
	std::fstream goodFile(tempGoodFileName, std::ios_base::app);
	goodFile << inStr << std::endl;
	goodFile.close();
      }
      else if(yesNo == 0){
	std::fstream badFile(tempBadFileName, std::ios_base::app);
	badFile << inStr << std::endl;
	badFile.close();
      }
    }
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  strVect_p->clear();
  delete strVect_p;

  return 0;
}


int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: addToMachineDatabase.exe <inputFile>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int result = addToMachineDatabase(argv[1]);

  return result;
}
