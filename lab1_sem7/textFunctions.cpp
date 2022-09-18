#include <iostream>
#include "textFunctions.h"

using namespace std;

bool ContainSeparators(const vector<char> separators, const char symbol) { // �������� ������� �� �������������� � ������������
    bool result = false;
    if (find(separators.begin(), separators.end(), symbol) != separators.end()) // ���� ������ ������ ����� ������������
    {
        result = true;
    }
    return result;
}

bool ContainSeparators(const vector<char> separators, const string str) { // �������� ����� �� ������� � �� ������������
    bool result = false;
    for (int i = 0; i <= str.size(); i++) {
        if (find(separators.begin(), separators.end(), str[i]) != separators.end()) // ���� ������ ������ ����� ������������
        {
            result = true;
            return result;
        }
    }
    return result;
}

void SplitText(const vector<string>& text, vector<string>& wordsWithSearchSymbol) { // ���������� ������ �� ��������� �����
    string word = "";
    vector<string> tempVec;
    const vector<char> separators = { ' ', '.', ',', '!', '?', '\t', '\n', '|', '\\', '@', '"', '#',
      '$', '%', ':', '*', '(', ')', '[', ']', '-', '_', '+', '=', '{', '}', '/', ';', '<', '>', '^' };
    for (int i = 0; i < text.size(); i++) {
        int j = 0;
        if (text[i].empty()) {
            continue;
        }
        while (text[i][j] != '\0') { // �������� ������ �� �����������
            if (!ContainSeparators(separators, text[i][j]) && (text[i][j] != string::npos)) { // ���� ������ �� ����������� � ������������
                word.push_back(text[i][j]); // ���������� ������� � �����
            }
            if (ContainSeparators(separators, text[i][j + 1]) || (j == text[i].length() - 1)) { // ���� ��������� ������ �� ����������� � ������������ ��� ��������� ������ �������� ���������
                tempVec.push_back(word);
                word.clear();
            }
            j++;
        }
    }
    for (int i = 0; i < tempVec.size(); i++) { // ������������� �������� ���������� �������
        if (!ContainSeparators(separators, tempVec[i]) && tempVec[i] != "") {
            wordsWithSearchSymbol.push_back(tempVec[i]);
        }
    }
}

void FindSymbolInText(vector<string>& wordsWithSearchSymbol, string searchSymbol) { // ����� ������� � ������ 
    vector<string> tempVec;
    for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
        string word = wordsWithSearchSymbol[i];
        transform(word.begin(), word.end(), word.begin(), ::tolower); // ���������� ����� � ��������� ��������
        transform(searchSymbol.begin(), searchSymbol.end(), searchSymbol.begin(), ::tolower); // ���������� �������� ������� � ��������� ��������
        if (word.find(searchSymbol) != string::npos) { // ���� � ����� ������ ������� ������
            tempVec.push_back(wordsWithSearchSymbol[i]);
        }
    }
    wordsWithSearchSymbol = tempVec;
}