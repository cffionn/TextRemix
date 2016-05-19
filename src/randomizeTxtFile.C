#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <boost/algorithm/string.hpp>

#include "include/globalDoDebug.h"
#include "include/checkOutputTxtFile.h"

int myrandom(int i){return std::rand()%i;}

int randomizeTxtFile(const std::string inFileName)
{
  if(!checkOutputTxtFile(inFileName)) return -1;
  
  std::ifstream inFile(inFileName);
  std::string str;
  std::vector<std::string>* strVect_p = new std::vector<std::string>;

  while(std::getline(inFile, str)){
    strVect_p->push_back(str);
  }
  inFile.close();

  std::srand(unsigned(std::time(NULL)));
  std::random_shuffle(strVect_p->begin(), strVect_p->end(), myrandom);
  
  std::ofstream outFile(inFileName);

  for(int iter = 0; iter < (int)strVect_p->size(); iter++){
    outFile << strVect_p->at(iter) << std::endl;
  }

  outFile.close();

  strVect_p->clear();
  delete strVect_p;

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: randomizeTxtFile.exe <inPath>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = randomizeTxtFile(argv[1]);
  return retVal;

}
