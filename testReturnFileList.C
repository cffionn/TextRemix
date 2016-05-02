#include "returnFileList.h"
#include <iostream>

int testReturnFileList(const std::string testPath, const std::string filterStr)
{
  std::vector<std::string> testFileVect = returnFileList(testPath, filterStr);
  std::cout << "Number of files (filter == \'" << filterStr << "\'): " << testFileVect.size() << std::endl;

  for(int iter = 0; iter < (int)testFileVect.size(); iter++){
    std::cout << " File #" << iter << ": " << testFileVect.at(iter) << std::endl;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 3){
    std::cout << "Usage: testReturnFileList.exe <inputWord> <filterStr>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = testReturnFileList(argv[1], argv[2]);
  return retVal;
}
