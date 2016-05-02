#include "interface/returnFileList.h"
#include "interface/getRhyme.h"
#include <iostream>

const std::string filterStr = ".txt";

int testGetRhyme(const std::string inWord)
{
  std::vector<std::string> testFileVect = returnFileList(rhymeDatabasePath, filterStr);
  std::cout << "Number of files (filter == \'" << filterStr << "\'): " << testFileVect.size() << std::endl;

  for(int iter = 0; iter < (int)testFileVect.size(); iter++){
    std::cout << " File #" << iter << ": " << testFileVect.at(iter) << std::endl;
  }

  return getRhyme(inWord, &testFileVect);
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: testGetRhyme.exe <inputWord>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = testGetRhyme(argv[1]);
  std::cout << "Rhyme pos: " << retVal << std::endl;
  return retVal;
}
