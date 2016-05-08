#include <iostream>
#include <fstream>
#include <vector>

#include "interface/getRhyme.h"
#include "interface/checkMakeDir.h"
#include "interface/returnFileList.h"


int expandRhymeDatabase()
{
  if(!checkDir(rhymeDatabasePath)){
    std::cout << "rhymeDatabasePath, \'" << rhymeDatabasePath << "\' not a directory. Return 1." << std::endl;
    return 1;
  }

  std::vector<std::string> rhymeFileList = returnFileList(rhymeDatabasePath, ".txt");
  
  if(rhymeFileList.size() == 0){
    std::cout << "rhymeDatabasePath, \'" << rhymeDatabasePath << "\' contains no files with filter .txt. Return 1." << std::endl;
    return 1;
  }

  if(-1 == orderRhymeFileList(&rhymeFileList)) return 1;

  for(int iter = 0; iter < (int)rhymeFileList.size(); iter++){
    std::cout << "File " << iter << "/" << rhymeFileList.size()-1 << ": " << rhymeFileList.at(iter) << std::endl;
  }

  return 0;
}

int main()
{
  int retVal;

  retVal = expandRhymeDatabase();

  return retVal;
}
