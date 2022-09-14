#include "fileSystem.h"
#include "userInterface.h"
#include "exceptions.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

bool IsPathGood(string path) { // �������� ����
  size_t found = path.find_last_of("\\");
  size_t point = path.find_last_of(".");
  size_t base = point - found - 1;
  string baseFilenameStr = path.substr(found + 1, base);
  const char* basefilenameChar = baseFilenameStr.c_str();
  ofstream file(path, ios::app);
  //if (!_strcmpi(basefilenameChar, "con")) {
  //  file.close(); // �� �� ����
  //  throw WrongPathInput("������������ �������� ���� ��� ����� �����.", filename, context);
  //}
  //if (!std::filesystem::is_regular_file(filename)) {   ����� ������ ��� 14 ���������
  //  file.close(); // �� �� ����
  //  throw WrongPathInput("������������ �������� ���� ��� ����� �����.", filename);
  //}
  //file.close();
  if (_strcmpi(basefilenameChar, "con")) return false;
  if (is_regular_file(path)) return false;
  file.close();
  return true;
}

bool IsReadOnly(string path) { // �������� ����� �� ������� "������ ��� ������"
  ofstream file(path);
  WIN32_FIND_DATAA findData;
  LPCSTR name = path.c_str();
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    //throw FileIsReadOnly("���������� ��������� ������ � ����, ��������������� ������ ��� ������.", context);
    return true;
  }
  return false;
}

void PathInput(string& path) {
  int userChoice;
  system("cls");
  cout << "������� ���� � �����: ";
  //cin.get();
  getline(cin, path);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  while (IsPathGood(path) || IsReadOnly(path)) { // �������� �� ���������� ���� � ��� �����
    if (IsPathGood(path)) {
      cerr << "������������ �������� ���� ��� ����� �����." << endl;
    }
    if (IsReadOnly(path)) {
      cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
    }
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
      PathInput(path);
      //switch (context) { // ����� ������, � ������� ��������f� ������
      //case SaveResultContext: {
      //  SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      //  break; }
      //case SaveInitialDataContext: {
      //  SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      //  break; }
      //case InputContext: {
      //  FileInput(text, searchSymbol);
      //  PrintText(text, searchSymbol);
      //  SplitText(text, wordsWithSearchSymbol);
      //  FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
      //  PrintResult(wordsWithSearchSymbol);
      //  SaveData(text, wordsWithSearchSymbol, searchSymbol);
      //  break; }
      //}
      break;
    }
    case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
      PrintMenu();
      break; }
    }
    /*cout << "������� ���� � �����: ";
    getline(cin, path);*/
  }
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

void FileInput(vector<string>& text, string& searchSymbol) { // ������� ��� ������ ������ �� �����
  text.clear();
  string pathInput = "";
  PathInput(pathInput);
  //system("cls");
  //cout << "������� ���� � �����: ";
  //getline(cin, pathInput);
  //CheckPath(pathInput);

  ifstream fin(pathInput);
  fin.seekg(0, ios::beg);
  string temp; // ���������� ��� ���������� �������� �������� �� �����
  int count = 0;
  while (!fin.eof()) {  // ��� ����� ����� ������ ������������� + �������� ���� � ��������� ������
    if (count == 0) {
      fin >> searchSymbol;
      count++;
    }
    while (getline(fin, temp))
      text.push_back(temp);
  }
  fin.close();
}

void SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, int saveContext) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
  //system("cls");
  //cout << "������� ���� � �����: ";
  //getline(cin, pathInput);
  //CheckPath(pathInput);
  //CheckReadOnly(pathOutput);
  int userChoice;
  string pathOutput;
  PathInput(pathOutput);
  ifstream fout(pathOutput);
  //cout << endl;
  fout.close();
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
      PrintMenu();
      break; }
    }
    //break;
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
  }
}