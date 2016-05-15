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
  int nFiles = (int)dbFileList.size();


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
