#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

using namespace std::experimental::filesystem;
using namespace std;

bool CheckPath(string filename) { // �������� ����
  size_t found = filename.find_last_of("\\");
  size_t point = filename.find_last_of(".");
  size_t base = point - found - 1;
  string baseFilenameStr = filename.substr(found + 1, base);
  const char* basefilenameChar = baseFilenameStr.c_str();
  ofstream file(filename, ios::app);
  if (!_strcmpi(basefilenameChar, "con")) return true;
  //if (!is_regular_file(filename)) return true;
  file.close();
  return false;
}

bool CheckReadOnly(string filename) { // �������� ����� �� ������� "������ ��� ������"
  ifstream file(filename);
  WIN32_FIND_DATAA findData;
  LPCSTR name = filename.c_str();
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
    return false;
  }
  else return true;
}

void PrintAdditionalMenu() { // ��������������� ����, ���� � ���� ���������� ����� ��� ��������� ��� ������������ ����. ���������� ������������ ���� ��� ������� ������ ���� � ����� ������
  cout << "������ ���� ��� ����������." << endl;
  cout << endl;
  cout << "\t��� �� ������ �������?" << endl;
  cout << "1. ������������ ����." << endl;
  cout << "2. ������� ����� ����." << endl;
  cout << "3. �����." << endl;
}

void PrintResult(const vector<string>& text, const vector<string>& redacted_text, string line_for_search, string path) { // ��������������� ������� ��� ������ ������ � ����
  ofstream fout(path);
  fout << "�������� �����: " << endl;
  fout << endl;
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
  fout << endl;
  if (text != redacted_text) {
    fout << "����� ����� ��������������: " << endl;
    fout << endl;
    for (int i = 0; i < redacted_text.size(); i++) {
      fout << redacted_text[i] << endl;
    }
    fout << endl;
  }
}

void PrintInitialData(const vector<string>& text, string path) { // ������� ��� ������ �������� ������ � ����
  ofstream fout(path);
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
}

vector<string> FileInput(vector<string>& text) { // ������� ��� ������ ������ �� �����
  string pathInput;
  cout << "������� ���� � �����: ";
  getline(cin, pathInput);
  ifstream fin(pathInput);
  while (true) {
    while (!fin || CheckPath(pathInput)) { // �������� �� ������������� ����� �� ���������� ����
      fin.close();
      cerr << "������������ �������� ���� ��� ����� �����." << endl;
      cout << "������� ���� � �����: ";
      getline(cin, pathInput);
      fin.open(pathInput); // �������� �����
      cout << endl;
    }
    break;
  }
  fin.seekg(0, ios::beg);
  string temp; // ���������� ��� ���������� �������� �������� �� �����
  while (!fin.eof()) {
    while (getline(fin, temp))
      text.push_back(temp);
  }
  fin.close();
  return text;
}

void SaveResult(const vector<string>& text, const vector<string>& redacted_text, string searchSymbol) { // ������� ��� ���������� ���������� � ����
  string pathOutput;
  int userChoice;
  cout << "������� ���� � �����: ";
  getline(cin, pathOutput);
  ifstream fout(pathOutput);
  while (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // �������� �� ���������� ���� � ��� �����
    fout.close();
    cerr << "������������ �������� ���� ��� ����� �����." << endl;
    cout << "������� ���� � �����: ";
    getline(cin, pathOutput);
    fout.open(pathOutput);
  }
  cout << endl;
  fout.close();
  while (fout) { // ���� ���� ��� ����������
    PrintAdditionalMenu(); // ����� ���������������� ����
    MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
    switch (userChoice) {
    case RewriteMenuItem: { // ������� � �����������
      ofstream fout(pathOutput);
      PrintResult(text, redacted_text, searchSymbol, pathOutput);
      fout.close();
      break; }
    case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
      fout.close();
      SaveResult(text, redacted_text, searchSymbol);
      break; }
    case GoBackMenuItem: { // ������� ����� �������
      // ;
      break; }
    }
    break;
  }
  if (!fout) { // ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
    PrintResult(text, redacted_text, searchSymbol, pathOutput);
    fout.close();
  }
}

void SaveInitialData(const vector<string>& text) {  // ������� ��� ������ �������� ������ � ����
  string pathOutput;
  int userChoice;
  cout << "������� ���� � �����: ";
  getline(cin, pathOutput);
  ifstream fout(pathOutput);
  while (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // �������� �� ���������� ���� � ��� �����
    fout.close();
    cerr << "������������ �������� ���� ��� ����� �����." << endl;
    cout << "������� ���� � �����: ";
    getline(cin, pathOutput);
    fout.open(pathOutput);
  }
  cout << endl;
  fout.close();
  while (fout) { // ���� ���� ��� ����������
    PrintAdditionalMenu(); // ����� ���������������� ����
    MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
    switch (userChoice) {
    case RewriteMenuItem: { // ������� � �����������
      ofstream fout(pathOutput);
      PrintInitialData(text, pathOutput);
      fout.close();
      break; }
    case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
      fout.close();
      SaveInitialData(text);
      break; }
    }
    break;
  }
  if (!fout) { // ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
    PrintInitialData(text, pathOutput);
    fout.close();
  }
}