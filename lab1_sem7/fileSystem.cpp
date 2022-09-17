#include "fileSystem.h"
#include "userInterface.h"
#include "exceptions.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

bool IsPathIncorrect(string path, int context) { // �������� ����
  size_t found = path.find_last_of("\\");
  size_t point = path.find_last_of(".");
  size_t base = point - found - 1;
  string basefilenameStr = path.substr(found + 1, base);
  const char* basefilenameChar = basefilenameStr.c_str();
  if (context == SaveContext) {
    fstream file(path, ios::app); // ���������� ��� ofstream
    if (!file) {
      file.close();
      return true;
    }
  }
  if (!_strcmpi(basefilenameChar, "con")) return true;
  if (!is_regular_file(path)) return true;
  return false;
}

bool IsReadOnly(string path) { // �������� ����� �� ������� "������ ��� ������"
  //ofstream file(path);
  WIN32_FIND_DATAA findData;
  LPCSTR name = path.c_str();
  FindFirstFileA(name, &findData);
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    return true;
  }
  else {
    return false;
  }
}

int PathInput(string& path, int context) {
  int userChoice;
  system("cls");
  cout << "������� ���� � �����: ";
  cin >> path;
  //getline(cin, path);
  //cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ifstream fout(path); // ��� ����������
  while (IsPathIncorrect(path, context) || IsReadOnly(path)) { // �������� �� ���������� ���� � ��� �����
    fout.close(); // ��� ����������
    if (IsPathIncorrect(path, context)) {
      cerr << "������������ �������� ���� ��� ����� �����." << endl;
      system("pause");
    }
    if (IsReadOnly(path)) {
      cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
      system("pause");
    }
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
      PathInput(path, context);
      break;
    }
    case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
      Menu();
      return ErrorInPathInput; // ��������� �� �� ����� RETURN ���� ������� ����
      break; }
    }
    /*cout << "������� ���� � �����: ";
    getline(cin, path);*/
  }
  return NoError;
}

void PrintAdditionalMenu() { // ��������������� ����, ���� � ���� ���������� ����� ��� ��������� ��� ������������ ����
  system("cls");
  cout << "������ ���� ��� ����������." << endl;
  cout << endl;
  cout << "\t��� �� ������ �������?" << endl;
  cout << "1. ������������ ����." << endl;
  cout << "2. ������� ����� ����." << endl;
  cout << "3. ��������� � ������� ����." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, string& path) { // ��������������� ������� ��� ������ ������ � ����
  ofstream fout(path);
  fout << "�������� �����: " << endl;
  fout << endl;
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
  fout << endl;
  fout << "������ ������: " << searchSymbol << endl;
  fout << endl;
  //if (text != wordsWithSearchSymbol) {
  fout << "�����, ������� ������ ������: " << endl;
  fout << endl;
  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    fout << wordsWithSearchSymbol[i] << endl;
    //}
    fout << endl;
  }
}

void PrintInitialData(const vector<string>& text, string& path) { // ������� ��� ������ �������� ������ � ����
  ofstream fout(path);
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
}

int FileInput(vector<string>& text, string& searchSymbol) { // ������� ��� ������ ������ �� �����
  text.clear();
  string pathInput = "";
  int res = PathInput(pathInput, InputContext);
  if (res == NoError) {
    ifstream fin(pathInput);
    fin.seekg(0, ios::beg);
    string temp; // ���������� ��� ���������� �������� �������� �� �����
    int count = 0;
    while (!fin.eof()) {  // ��� ����� ����� ������ ������������� + �������� ���� � ��������� ������
      temp = "";
      if (count == 0) {
        fin >> searchSymbol;
        count++;
      }
      while (getline(fin, temp))
        text.push_back(temp);
    }
    fin.close();
    return NoError;
  }
  else {
    return ErrorInFileFuncs;
  }
}

int SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, int saveContext) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
  int userChoice;
  string pathOutput;
  int res = PathInput(pathOutput, SaveContext);
  if (res == NoError) {
    remove(pathOutput);
    ifstream fout(pathOutput); // �� fstream
    //fout.close(); // �� �����
    /*while*/ if (fout) { // ���� ���� ��� ����������
      PrintAdditionalMenu(); // ����� ���������������� ����
      MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
      switch (userChoice) {
      case RewriteMenuItem: { // ������� � �����������
        ofstream fout(pathOutput);
        switch (saveContext) {
        case SaveResultContext: { // ���������� �����������
          PrintResult(text, wordsWithSearchSymbol, searchSymbol, pathOutput);
          fout.close();
          break; }
        case SaveInitialDataContext: { // ���������� �������� ������
          fout.close();
          PrintInitialData(text, pathOutput);
          break; }
        }
        break;
      }
      case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
        fout.close();
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, saveContext);
        break;
      }
      case GoBackMenuItem: { // ������� ����� � ������� ����
        Menu();
        break; }
      }
      //break;
      return NoError;
    }
    if (!fout) { // ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
      switch (saveContext) {
      case SaveResultContext: {
        PrintResult(text, wordsWithSearchSymbol, searchSymbol, pathOutput);
        break; }
      case SaveInitialDataContext: {
        PrintInitialData(text, pathOutput);
        break; }
      }
      fout.close();
      return NoError;
    }
  }
  else {
    return ErrorInFileFuncs;
  }
}