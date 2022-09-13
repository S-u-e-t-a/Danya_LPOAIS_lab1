#include <iostream>
#include "textFunctions.h"

using namespace std;

void SplitText(const vector<string>& text, vector<string>& wordsWithSearchSymbol) {
  string word = "";
  vector<char> separators = { ' ', '.', ',', '!', '?', '\t', '|', '\\', '@', '"', '#', '$', '%', ':', '*', '(', ')', '[', ']', '-', '_', '+', '=', '{', '}', '/', ';', '<', '>' };

  for (int i = 0; i < text.size(); i++) {
    int j = 0;
    if (text[i].empty())
    {
      continue;
    }
    while (text[i][j] != '\0') {
      //if (/*(text[i][j] != ' ' || text[i][j] != '\t' || text[i][j] != '/')*/ /*&& letters.find(text[i][j])*/ (find(separators.begin(), separators.end(), text[i][j]) != separators.end()) /*separators.find(text[i][j])*/ != string::npos) {
      //  word.push_back(text[i][j]);
      //}
      //if (/*word == Word && ((text[i][j + 1] == ' ') || (text[i][j + 1] == '/') || (text[i][j + 1] == '\t')*/ (!separators.find(text[i][j + 1]) || (j == text[i].length() - 1))) {
      //  wordsWithSearchSymbol.push_back(word);
      //}
      //j++;
      if (binary_search(separators.begin(), separators.end(), text[i][j]) != string::npos) {
        word.push_back(text[i][j]);
      }
      if (!binary_search(separators.begin(), separators.end(), text[i][j]) || (j == text[i].length() - 1)) {
        wordsWithSearchSymbol.push_back(word);
      }
      j++;
    }
    //for (int j = 0; j < text[i].length(); j++)
    //{
    //  if (text[i][j] == ' ' ) {
    //    wordsWithSearchSymbol.push_back(word);
    //    word = "";
    //  }
    //  else {
    //    word.push_back(text[i][j]);
    //  }
    //}
    //wordsWithSearchSymbol.push_back(word);
    //}
  }
}

void FindSymbolInText(vector<string>& wordsWithSearchSymbol, const string& searchSymbol) {
  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    if (wordsWithSearchSymbol[i].find(searchSymbol) != string::npos) {
      wordsWithSearchSymbol.erase(wordsWithSearchSymbol.begin() + i);  // мб i - 1
    }
  }
}


//Подсчёт количества символов, слов, строк, абзацев в тексте
void Count_Amount_In_Text(const vector<string>& text) {
  string letters = "qwetryuiopasdfghjklzxcbvnmйцукенгшщзхъфывапрлоджэячсмитьбюQWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
  string numbers = "0123456789";

  int words_count, paragraphs_count;

  words_count = 0;
  paragraphs_count = 0;

  for (int i = 0; i < text.size(); i++) {

    const char* str = text[i].c_str();
    int j = 0;
    int word = 0;
    if (str[0] == '\t')
      paragraphs_count++;
    while (str[j] != '\0') {
      if (str[j] == ' ' || str[j] == '\t' || str[j] == '/') {
        word = Separator;
      }
      if (numbers.find(str[j]) != string::npos) {
        word = Number;
      }
      if ((str[j] != ' ' || str[j] != '\t' || str[j] != '/') && letters.find(str[j]) != string::npos) {
        word = Word;
      }
      if (word == Word && ((str[j + 1] == ' ') || (str[j + 1] == '/') || (str[j + 1] == '\t') || (j == text[i].length() - 1))) {
        words_count++;
      }
      j++;
    }
  }
}

//Конвертация к строчным буквам
size_t ConvertToLower(string text, string searchSymbol, size_t pos = 0) {
  transform(text.begin(), text.end(), text.begin(), ::tolower);
  transform(searchSymbol.begin(), searchSymbol.end(), searchSymbol.begin(), ::tolower);
  return text.find(searchSymbol, pos);
}

//Поиск подстроки
int SearchForString(const vector<string>& text, string line_for_search) {
  int counter = 0;
  for (int i = 0; i < text.size(); i++) {
    size_t pos = ConvertToLower(text[i], line_for_search);
    while (pos != string::npos) {
      counter++;
      pos = ConvertToLower(text[i], line_for_search, pos + line_for_search.size());
    }
  }
  return counter;
}