#include "interface/globalDoDebug.h"
#include "interface/returnFileList.h"
#include "interface/getRhyme.h"
#include <iostream>

const std::string filterStr = ".txt";

int testGetRhyme(const std::string inWord, bool doInteractiveRhyme)
{
  std::vector<std::string> testFileVect = returnFileList(rhymeDatabasePath, filterStr);
  std::cout << "Number of files (filter == \'" << filterStr << "\'): " << testFileVect.size() << std::endl;

  for(int iter = 0; iter < (int)testFileVect.size(); iter++){
    std::cout << " File #" << iter << ": " << testFileVect.at(iter) << std::endl;
  }

  return getRhyme(inWord, &testFileVect, doInteractiveRhyme);
}

int main(int argc, char *argv[])
{
  if(argc != 3){
    std::cout << "Usage: testGetRhyme.exe <inputWord> <doInteractiveRhyme>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }
  else{
    std::string testBoolInput = argv[2];
    if(testBoolInput.size() != 1){
      std::cout << "Arg 2 \'" << testBoolInput << "\' not boolean. Please give 0 or 1. Return -1." << std::endl;
      return -1;
    }
    else if(testBoolInput.find("0") == std::string::npos && testBoolInput.find("1") == std::string::npos){
      std::cout << "Arg 2 \'" << testBoolInput << "\' not boolean. Please give 0 or 1. Return -1." << std::endl;
      return -1;
    }
  }


  int retVal = testGetRhyme(argv[1], argv[2]);
  std::cout << "Rhyme pos: " << retVal << std::endl;
  return retVal;
}
