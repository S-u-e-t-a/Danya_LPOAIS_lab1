#include <iostream>
#include "textFunctions.h"

using namespace std;

bool ContainSeparators(const vector<char> separators, const char symbol) { // Проверка символа на принадлежность к разделителям
    bool result = false;
    if (find(separators.begin(), separators.end(), symbol) != separators.end()) // Если символ найден среди разделителей
    {
        result = true;
    }
    return result;
}

bool ContainSeparators(const vector<char> separators, const string str) { // Проверка слова на наличие в нём разделителей
    bool result = false;
    for (int i = 0; i <= str.size(); i++) {
        if (find(separators.begin(), separators.end(), str[i]) != separators.end()) // Если символ найден среди разделителей
        {
            result = true;
            return result;
        }
    }
    return result;
}

void SplitText(const vector<string>& text, vector<string>& wordsWithSearchSymbol) { // Разделение текста на отдельные слова
    string word = "";
    vector<string> tempVec;
    const vector<char> separators = { ' ', '.', ',', '!', '?', '\t', '\n', '|', '\\', '@', '"', '#',
      '$', '%', ':', '*', '(', ')', '[', ']', '-', '_', '+', '=', '{', '}', '/', ';', '<', '>', '^' };
    for (int i = 0; i < text.size(); i++) {
        int j = 0;
        if (text[i].empty()) {
            continue;
        }
        while (text[i][j] != '\0') { // Проверка строки на разделители
            if (!ContainSeparators(separators, text[i][j]) && (text[i][j] != string::npos)) { // Если символ не принадлежит к разделителям
                word.push_back(text[i][j]); // Добавление символа в слово
            }
            if (ContainSeparators(separators, text[i][j + 1]) || (j == text[i].length() - 1)) { // Если следующий символ не принадлежит к разделителям или следующий символ является последним
                tempVec.push_back(word);
                word.clear();
            }
            j++;
        }
    }
    for (int i = 0; i < tempVec.size(); i++) { // Окончательная проверка временного вектора
        if (!ContainSeparators(separators, tempVec[i]) && tempVec[i] != "") {
            wordsWithSearchSymbol.push_back(tempVec[i]);
        }
    }
}

void FindSymbolInText(vector<string>& wordsWithSearchSymbol, string searchSymbol) { // Поиск символа в тексте 
    vector<string> tempVec;
    for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
        string word = wordsWithSearchSymbol[i];
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Приведение слова к строчному регистру
        transform(searchSymbol.begin(), searchSymbol.end(), searchSymbol.begin(), ::tolower); // Приведение искомого символа к строчному регистру
        if (word.find(searchSymbol) != string::npos) { // Если в слове найден искомый символ
            tempVec.push_back(wordsWithSearchSymbol[i]);
        }
    }
    wordsWithSearchSymbol = tempVec;
}