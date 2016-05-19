#ifndef GETWORDSFROMSENTENCE_H
#define GETWORDSFROMSENTENCE_H

#include <string>
#include <vector>

#include "include/globalDoDebug.h"
#include "include/defAlphaNumSoup.h"

void getWordsFromSentence(std::string sentence, std::vector<std::string>* words_p)
{
  sentence = replaceNumbersWithWords(sentence);

  int sentenceIter = 0;
  while(sentenceIter < (int)sentence.size()){
    if(alphabetSoup.find(sentence.at(sentenceIter)) == std::string::npos){
      sentence.erase(sentence.begin()+sentenceIter);
    }
    else sentenceIter++;
  }

  while(sentence.find("  ") != std::string::npos){
    sentence.erase(sentence.find("  "), 1);
  }

  while(true){
    std::size_t tempPos = sentence.find(" ");
    if(tempPos == std::string::npos){
      words_p->push_back(sentence);
      break;
    }
    words_p->push_back(sentence.substr(0, tempPos));
    sentence = sentence.substr(tempPos+1, sentence.size()-tempPos+1);
  }

  return;
}

#endif
