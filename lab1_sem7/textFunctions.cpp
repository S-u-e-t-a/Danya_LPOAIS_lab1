#include <iostream>
#include "textFunctions.h"

using namespace std;

bool ContainSeparators(const vector<char> separators, const char symbol)
{
  bool result = false;
  if (find(separators.begin(), separators.end(), symbol) != separators.end())
  {
    result = true;
  }
  return result;
}

bool ContainSeparators(const vector<char> separators, const string s)
{
  bool result = false;
  for (int i = 0; i <= s.size(); i++) {
    if (find(separators.begin(), separators.end(), s[i]) != separators.end())
    {
      result = true;
      return result;
    }
  }
  return result;
}

void SplitText(const vector<string>& text, vector<string>& wordsWithSearchSymbol) {
  string word = "";
  vector<string> tempVec;
  vector<char> separators = { ' ', '.', ',', '!', '?', '\t', '\n', '|', '\\', '@', '"', '#', '$', '%', ':', '*', '(', ')', '[', ']', '-', '_', '+', '=', '{', '}', '/', ';', '<', '>', '^'};
  for (int i = 0; i < text.size(); i++) {
    int j = 0;
    if (text[i].empty()) {
      continue;
    }
    while (text[i][j] != '\0') {
      if (!ContainSeparators(separators, text[i][j]) && (text[i][j] != string::npos)) {
        word.push_back(text[i][j]);
      }
      if (ContainSeparators(separators, text[i][j + 1]) || (j == text[i].length() - 1)) {
        tempVec.push_back(word);
        word.clear();
      }
      j++;
    }
    //remove(wordsWithSearchSymbol.begin(), wordsWithSearchSymbol.end(), "");
  }
  for (int i = 0; i < tempVec.size(); i++) {
    if (!ContainSeparators(separators, tempVec[i]) && tempVec[i] != "") {
      wordsWithSearchSymbol.push_back(tempVec[i]);
    }
  }
}

void FindSymbolInText(vector<string>& wordsWithSearchSymbol, string searchSymbol) {
  // создать временный вектор и в него записывать результат
  vector<string> tempVec;

  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    string tempWord = wordsWithSearchSymbol[i];
    transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower);
    transform(searchSymbol.begin(), searchSymbol.end(), searchSymbol.begin(), ::tolower);
    //if (!(tempWord.find(searchSymbol) != string::npos)) { // если не нашёл. убрать ! если хочу добавлять в новый вектор
    //  remove(wordsWithSearchSymbol.begin(), wordsWithSearchSymbol.end(), tempWord);
    //}
    if (tempWord.find(searchSymbol) != string::npos) {
      tempVec.push_back(tempWord);
    }
  }
  wordsWithSearchSymbol = tempVec;
  //remove(wordsWithSearchSymbol.begin(), wordsWithSearchSymbol.end(), "");
}