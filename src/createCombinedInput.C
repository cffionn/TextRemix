#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "include/globalDoDebug.h"
#include "include/defAlphaNumSoup.h"
#include "include/checkMakeDir.h"

const std::string outDirCombo = "outputCombo/";

int createCombinedInput(const std::string inFileName, const std::string inFileName2)
{
  std::ifstream file;
  std::string str;
  
  std::vector<std::string>* inStr1_p = new std::vector<std::string>;
  std::vector<std::string>* inStr2_p = new std::vector<std::string>;

  if(inFileName.find(".txt") != std::string::npos){
    file.open(inFileName.c_str());
    while(std::getline(file, str)){
      while(str.substr(0, 1).find(" ") != std::string::npos){
        str.replace(0, 1, "");
      }

      if(str.find("\r") != std::string::npos) str = str.substr(0, str.find("\r"));

      inStr1_p->push_back(str);
    }
    file.close();
  }
  else{
    std::cout << "inFileName 1, \'" << inFileName << "\' is invalid. Not \'.txt\'. Return 1." << std::endl;
    return 1;
  }

  if(inFileName2.find(".txt") != std::string::npos){
    file.open(inFileName2.c_str());
    while(std::getline(file, str)){
      while(str.substr(0, 1).find(" ") != std::string::npos){
        str.replace(0, 1, "");
      }

      if(str.find("\r") != std::string::npos) str = str.substr(0, str.find("\r"));

      inStr2_p->push_back(str);
    }
    file.close();
  }
  else{
    std::cout << "inFileName 2, \'" << inFileName2 << "\' is invalid. Not \'.txt\'. Return 1." << std::endl;
    return 1;
  }

  const int inStr1Size = (int)inStr1_p->size();
  const int inStr2Size = (int)inStr2_p->size();

  if(inStr1Size == 0){
    std::cout << "Input file 1 empty. Return 1" << std::endl;
    return 1;
  }

  if(inStr2Size == 0){
    std::cout << "Input file 2 empty. Return 1" << std::endl;
    return 1;
  }

  std::string outName;
  int lead = -1;
  int pos = 0;
  std::string tempInFileName = inFileName;
  std::string tempInFileName2 = inFileName2;

  std::string repStr = "_ComboOutput.txt";

  while(tempInFileName.find("/") != std::string::npos){
    tempInFileName.replace(0, tempInFileName.find("/")+1, "");
  }

  while(tempInFileName.find(repStr) != std::string::npos){
    tempInFileName.replace(tempInFileName.find(repStr), repStr.size(), "");
  }

  while(tempInFileName2.find("/") != std::string::npos){
    tempInFileName2.replace(0, tempInFileName2.find("/")+1, "");
  }

  while(tempInFileName2.find(repStr) != std::string::npos){
    tempInFileName2.replace(tempInFileName2.find(repStr), repStr.size(), "");
  }

  while(lead == -1 && pos < (int)tempInFileName.size() && pos <  (int)tempInFileName2.size()){
    std::string tempChar1 = tempInFileName.substr(pos, 1);
    std::string tempChar2 = tempInFileName2.substr(pos, 1);

    if(!strcmp(tempChar1.c_str(), ".")) lead = 0;
    else if(!strcmp(tempChar2.c_str(), ".")) lead = 1;

    if(lead != -1) break;

    if(alphabetSoup.find(tempChar1.c_str()) == std::string::npos){
      std::cout << "Non-alphanumeric char in inFileName1, \'" + tempInFileName + "\'. Return 1." << std::endl;
      return 1;
    }
    else if(alphabetSoup.find(tempChar2.c_str()) == std::string::npos){
      std::cout << "Non-alphanumeric char in inFileName2, \'" + tempInFileName2 + "\'. Return 1." << std::endl;
      return 1;
    }

    boost::algorithm::to_lower(tempChar1);
    boost::algorithm::to_lower(tempChar2);

    int tempPos1 = alphabetSoup.find(tempChar1.c_str());
    int tempPos2 = alphabetSoup.find(tempChar2.c_str());
    if(tempPos1 > tempPos2){
      lead = 1;
    }
    else if(tempPos2 > tempPos1){
      lead = 0;
    }

    pos++;
  }

  if(lead != 0 && lead != 1){
    std::cout << "Sorting of file names failed. Return 1." << std::endl;
    return 1;
  }
  else if(lead == 0){
    if(tempInFileName.find(".txt") != std::string::npos) tempInFileName.replace(tempInFileName.find(".txt"), 4, "");
    outName = tempInFileName + "_" + tempInFileName2;
  }
  else if(lead == 1){
    if(tempInFileName2.find(".txt") != std::string::npos) tempInFileName2.replace(tempInFileName2.find(".txt"), 4, "");
    outName = tempInFileName2 + "_" + tempInFileName;
  }

  std::string tempOutName = outName;
  if(tempOutName.find(".txt") != std::string::npos){
    tempOutName.replace(tempOutName.find(".txt"), 4, repStr);
  }
  tempOutName = outDirCombo + tempOutName;

  if(checkMakeDir(outDirCombo)){
    std::ofstream outFile(tempOutName.c_str());

    for(int iter = 0; iter < inStr1Size; iter++){
      outFile << inStr1_p->at(iter) << std::endl;
    }

    for(int iter = 0; iter < inStr2Size; iter++){
      outFile << inStr2_p->at(iter) << std::endl;
    }

    outFile.close();
  }
  else{
    std::cout << "Error making dir \'" << outDirCombo << "\'. File \'" << tempOutName << "\' not written." << std::endl;
  }

 
  inStr2_p->clear();
  delete inStr2_p;

  inStr1_p->clear();
  delete inStr1_p;

  return 0;
}


int main(int argc, char *argv[])
{
  if(argc != 3){
    std::cout << "Usage: createCombinedInput.exe <inputFile> <inputFile2>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int result = createCombinedInput(argv[1], argv[2]);

  return result;
}

