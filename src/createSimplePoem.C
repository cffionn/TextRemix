#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"


int createSimplePoem(const std::string inFileName)
{
  if((int)inFileName.size() < 4){
    
  }

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: createSimplePoem.exe <inputFile>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int result = createSimplePoem(argv[1]);

  return result;
}
