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

void SplitText(const vector<string>& text, vector<string>& wordsWithSearchSymbol) {
  string word = "";
  vector<char> separators = { ' ', '.', ',', '!', '?', '\t', '\n', '|', '\\', '@', '"', '#', '$', '%', ':', '*', '(', ')', '[', ']', '-', '_', '+', '=', '{', '}', '/', ';', '<', '>'};
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
        wordsWithSearchSymbol.push_back(word);
        word.clear();
      }
      j++;
    }
    remove(wordsWithSearchSymbol.begin(), wordsWithSearchSymbol.end(), "");
  }
}

void FindSymbolInText(vector<string>& wordsWithSearchSymbol, string searchSymbol) {
  // создать временный вектор и в него записывать результат
  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    string tempWord = wordsWithSearchSymbol[i];
    transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower);
    transform(searchSymbol.begin(), searchSymbol.end(), searchSymbol.begin(), ::tolower);
    if (!(tempWord.find(searchSymbol) != string::npos)) { // если не нашёл. убрать ! если хочу добавлять в новый вектор
      remove(wordsWithSearchSymbol.begin(), wordsWithSearchSymbol.end(), tempWord);
    }
  }
  remove(wordsWithSearchSymbol.begin(), wordsWithSearchSymbol.end(), "");
}