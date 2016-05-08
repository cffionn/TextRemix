#include <iostream>
#include <fstream>
#include <vector>

#include "interface/getRhyme.h"
#include "interface/checkMakeDir.h"
#include "interface/returnFileList.h"


int expandRhymeDatabase()
{
  if(!checkDir(rhymeDatabasePath)){
    std::cout << "Something wrong with global rhymeDatabasePath, \'" << rhymeDatabasePath << "\'. Return 1." << std::endl;
    return 1;
  }

  std::vector<std::string> rhymeFileList = returnFileList(rhymeDatabasePath, ".txt");
  
  

  return 0;
}

int main()
{
  int retVal;

  retVal = expandRhymeDatabase();

  return retVal;
}
