#include "interface/globalDoDebug.h"
#include "interface/getSyllable.h"

int testGetSyllable(const std::string testWord)
{
  int syl = getSyllables(testWord);
  std::cout << "Number of syllables: " << syl << std::endl;
  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    std::cout << "Usage: testGetSyllable.exe <inputWord>" << std::endl;
    std::cout << "Number of args given: " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = testGetSyllable(argv[1]);
  return retVal;
}
