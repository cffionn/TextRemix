#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"
#include "include/checkOutputTxtFile.h"

const std::string macDBDirStr = "machineDatabase/";
const std::string goodFileName = "goodStrings.txt";
const std::string badFileName = "badStrings.txt";

int addToMachineDatabase(const std::string inFileName)
{
  if(!checkOutputTxtFile(inFileName)) return -1;

  std::ifstream inFile(inFileName);
  std::string str;
  std::vector<std::string>* strVect_p = new std::vector<std::string>;

  while(std::getline(inFile, str)){
    strVect_p->push_back(str);
  }
  inFile.close();

  const int nStr = (int)strVect_p->size();
  
  std::vector<std::string>* goodStrings_p = new std::vector<std::string>;
  std::vector<std::string>* badStrings_p = new std::vector<std::string>;

  for(int iter = 0; iter < nStr; iter++){
    int yesNo = -1;

    
    std::cout << "\'" << strVect_p->at(iter) << "\'" << std::endl;
    std::cout << "  Is string good? (y/n): ";

    std::string input;
    std::cin >> input;

    yesNo = parseYesNo(input);
  }

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
