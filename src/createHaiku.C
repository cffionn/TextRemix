#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "include/globalDoDebug.h"
#include "include/checkOutputTxtFile.h"
#include "include/getSyllable.h"

int myrandom(int i){return std::rand()%i;}

int createSimplePoem(const std::string inFileName)
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

  int strSize = (int)strVect_p->size();
    
  std::vector<std::string>* fiveSyl_p = new std::vector<std::string>;
  std::vector<std::string>* sevenSyl_p = new std::vector<std::string>;

  for(int iter = 0; iter < strSize; iter++){
    std::string sentence1 = strVect_p->at(iter);
        
    int syl = getSyllables(sentence1);

    if(syl == 5) fiveSyl_p->push_back(sentence1);
    else if(syl == 7) sevenSyl_p->push_back(sentence1);
  }

  if((int)fiveSyl_p->size() < 2){
    std::cout << "Not enough 5 syllable lines in file \'" << inFileName << "\'. Return -1" << std::endl;
    return -1;
  }
  if((int)sevenSyl_p->size() < 1){
    std::cout << "Not enough 7 syllable lines in file \'" << inFileName << "\'. Return -1" << std::endl;
    return -1;
  }

  std::string outFileName = inFileName;
  outFileName.replace(outFileName.find(".txt"), 4, "");
  outFileName = outFileName + "_Haiku.txt";

  std::ofstream outFile(outFileName);
  outFile << fiveSyl_p->at(0) << std::endl;
  outFile << sevenSyl_p->at(0) << std::endl;
  outFile << fiveSyl_p->at(1) << std::endl;
  outFile.close();

  fiveSyl_p->clear();
  delete fiveSyl_p;

  sevenSyl_p->clear();
  delete sevenSyl_p;

  strVect_p->clear();
  delete strVect_p;

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
