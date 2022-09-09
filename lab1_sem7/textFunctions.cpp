#include <iostream>
#include "textFunctions.h"

using namespace std;
//
////Подсчёт количества символов, слов, строк, абзацев в тексте
//amount_in_text Count_Amount_In_Text(const vector<string>& text) {
//  string letters = "qwetryuiopasdfghjklzxcbvnmйцукенгшщзхъфывапрлоджэячсмитьбюQWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
//  string numbers = "0123456789";
//  int symbols_count, words_count, lines_count, paragraphs_count;
//  symbols_count = 0;
//  words_count = 0;
//  lines_count = 0;
//  paragraphs_count = 0;
//  lines_count = distance(text.begin(), text.end());
//  for (int i = 0; i < text.size(); i++) {
//    symbols_count += text[i].length();
//    const char* str = text[i].c_str();
//    int j = 0;
//    int word = 0;
//    if (str[0] == '\t')
//      paragraphs_count++;
//    while (str[j] != '\0') {
//      if (str[j] == ' ' || str[j] == '\t' || str[j] == '/') {
//        word = Separator;
//      }
//      if (numbers.find(str[j]) != string::npos) {
//        word = Number;
//      }
//      if ((str[j] != ' ' || str[j] != '\t' || str[j] != '/') && letters.find(str[j]) != string::npos) {
//        word = Word;
//      }
//      if (word == Word && ((str[j + 1] == ' ') || (str[j + 1] == '/') || (str[j + 1] == '\t') || (j == text[i].length() - 1))) {
//        words_count++;
//      }
//      j++;
//    }
//  }
//  return { symbols_count, words_count, lines_count, paragraphs_count };
//}
//
////Копирование строки
//vector<string> Copy_String(vector<string>& redacted_text, int number_of_string_for_copy, int number_of_string) {
//  string new_string;
//  new_string = redacted_text[number_of_string_for_copy];
//  redacted_text.insert(redacted_text.begin() + number_of_string, new_string);
//  return redacted_text;
//}
//
////Конвертация к строчным буквам
//size_t Conver_To_Lower(string text, string line_for_search, size_t pos = 0) {
//  transform(text.begin(), text.end(), text.begin(), ::tolower);
//  transform(line_for_search.begin(), line_for_search.end(), line_for_search.begin(), ::tolower);
//  return text.find(line_for_search, pos);
//}
//
////Поиск подстроки
//int Search_For_String(const vector<string>& text, string line_for_search) {
//  int counter = 0;
//  for (int i = 0; i < text.size(); i++) {
//    size_t pos = Conver_To_Lower(text[i], line_for_search);
//    while (pos != string::npos) {
//      counter++;
//      pos = Conver_To_Lower(text[i], line_for_search, pos + line_for_search.size());
//    }
//  }
//  return counter;
//}