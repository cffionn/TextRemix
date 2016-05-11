#ifndef DEFALPHANUMSOUP_H
#define DEFALPHANUMSOUP_H

#include <string>

#include "interface/globalDoDebug.h"

const std::string alphabetSoup = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";
const std::string alphabetSoupUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string alphabetSoupLower = "abcdefghijklmnopqrstuvwxyz";
const std::string alphabetSoupConsonant = "BCDFGHJKLMNPQRSTVWXYZ bcdfghjklmnpqrstvwxyz";
const std::string alphabetSoupVowel = "AEIOU aeiou";

const std::string digitSoup = "0123456789";

const int nNumbers = 21;
const std::string numberSoup[nNumbers] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
const std::string numberSoupStr[nNumbers] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty"};

const std::string numberSoup2[nNumbers] = {"0th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th"};
const std::string numberSoup2Str[nNumbers] = {"zeroeth", "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth"};

const int nNumBack = 6;
const std::string numBack[nNumBack] = {" ", ".", ",", "!", "?", "'"};


std::string replaceNumbersWithWords(std::string inSentence)
{
  for(int iter = 0; iter < nNumbers; iter++){
    for(int iter2 = 0; iter2 < nNumBack; iter2++){
      std::string tempNumberSoup = " " + numberSoup[iter] + numBack[iter2];
      while(inSentence.find(tempNumberSoup.c_str()) != std::string::npos){
	inSentence.replace(inSentence.find(tempNumberSoup.c_str()), tempNumberSoup.size(), " " + numberSoupStr[iter] + numBack[iter2]);
      }
    }
  }

  for(int iter = 0; iter < nNumbers; iter++){
    std::string tempNumberSoup2 = " " + numberSoup2[iter];
    while(inSentence.find(tempNumberSoup2.c_str()) != std::string::npos){
      inSentence.replace(inSentence.find(tempNumberSoup2.c_str()), tempNumberSoup2.size(), " " + numberSoup2Str[iter]);
    }
  }

  return inSentence;
}

#endif
