#include "fileSystem.h"
#include "userInterface.h"
#include "exceptions.h"
#include <Windows.h>

using namespace std::experimental::filesystem;
using namespace std;

void CheckPath(string filename) { // �������� ����
  size_t found = filename.find_last_of("\\");
  size_t point = filename.find_last_of(".");
  size_t base = point - found - 1;
  string baseFilenameStr = filename.substr(found + 1, base);
  const char* basefilenameChar = baseFilenameStr.c_str();
  ofstream file(filename, ios::app);
  if (!_strcmpi(basefilenameChar, "con")) {
    file.close(); // �� �� ����
    throw WrongPathInput("������������ �������� ���� ��� ����� �����.", filename);
  }
  if (!std::filesystem::is_regular_file(filename)) {
    file.close(); // �� �� ����
    throw WrongPathInput("������������ �������� ���� ��� ����� �����.", filename);
  }
  file.close();

  //throw WrongPathInput("������������ �������� ���� ��� ����� �����.", filename); // ����� ������� VOID � �� BOOL

  //return false;
}

void CheckReadOnly(string filename) { // �������� ����� �� ������� "������ ��� ������"
  ifstream file(filename);
  WIN32_FIND_DATAA findData;
  LPCSTR name = filename.c_str();
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
    throw FileIsReadOnly("���������� ��������� ������ � ����, ��������������� ������ ��� ������."); // ����� ������� VOID � �� BOOL
    //return false;
  }
  //else return true;
}

void PrintAdditionalMenu() { // ��������������� ����, ���� � ���� ���������� ����� ��� ��������� ��� ������������ ����
  system("cls");
  cout << "������ ���� ��� ����������." << endl;
  cout << endl;
  cout << "\t��� �� ������ �������?" << endl;
  cout << "1. ������������ ����." << endl;
  cout << "2. ������� ����� ����." << endl;
  cout << "3. �����." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintErrorMenu() { // ��������������� ����, ���� � ���� �������� �������� ��������� ������
  system("cls");
  cout << "\t��� �� ������ �������?" << endl;
  cout << "1. ������ ������ ������." << endl;
  cout << "2. �����." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, string path) { // ��������������� ������� ��� ������ ������ � ����
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

void PrintInitialData(const vector<string>& text, string path) { // ������� ��� ������ �������� ������ � ����
  ofstream fout(path);
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
}

void FileInput(vector<string>& text) { // ������� ��� ������ ������ �� �����
  system("cls");
  text.clear();
  string pathInput;
  cout << "������� ���� � �����: ";
  getline(cin, pathInput);

  //CheckPath(pathInput) ���� ���������� ������, �� ��� �����

  ifstream fin(pathInput);

  //if (!fin || CheckPath(pathInput)) { // �������� �� ������������� ����� �� ���������� ����
  //  fin.close();

    //throw WrongPathInput("������������ �������� ���� ��� ����� �����.\n", pathInput);

    //catch (WrongPathInput &ex) // � try catch ���������
    //{
    //  cerr << "������: " << ex.what() << endl;
    //  cout << "�������� �����: " << ex.GetDataState() << endl;
    //  cout << endl;
    //  int userChoice;
    //  PrintErrorMenu();
    //  MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
    //switch (userChoice) {
    //case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
    //  FileInput(vector<string>& text);
    //  break; }
    //case ErrorMenuItems::GoBackMenuItem: { // ������� ����� �������
    //  PrintMenu();
    //  break; }
    //}
  //}

  // ������
  //while (true) {
  //  while (!fin || CheckPath(pathInput)) { // �������� �� ������������� ����� �� ���������� ����
  //    
  //    PrintErrorMenu();
  //    getline(cin, pathInput);
  //    fin.open(pathInput); // �������� �����
  //    cout << endl;
  //  }
  //  break;
  //}

  fin.seekg(0, ios::beg);
  string temp; // ���������� ��� ���������� �������� �������� �� �����
  while (!fin.eof()) {
    while (getline(fin, temp))
      text.push_back(temp);
  }
  fin.close();
}

void SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, int saveContext) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
  string pathOutput;
  int userChoice;
  cout << "������� ���� � �����: ";
  getline(cin, pathOutput);
  //CheckPath(pathOutput) ���� ���������� ������, �� ��� �����
  //CheckReadOnly(pathOutput) ���� ���������� ������, �� ��� �����
  ifstream fout(pathOutput);

  //if (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // �������� �� ���������� ���� � ��� �����
  //  throw WrongPathInput("������������ �������� ���� ��� ����� �����.\n", pathInput);

  //  catch (WrongPathInput& ex) // � try catch ���������
  //  {
  //    cerr << "������: " << ex.what() << endl;
  //    cout << "�������� �����: " << ex.GetDataState() << endl;
  //    cout << endl;
  //    int userChoice;
  //    PrintErrorMenu();
  //    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
  //    switch (userChoice) {
  //    case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
  //      FileInput(vector<string>&text);
  //      break; }
  //    case ErrorMenuItems::GoBackMenuItem: { // ������� ����� �������
  //      PrintMenu();
  //      break; }
  //    }
  //  }
  
    // ������
    //while (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // �������� �� ���������� ���� � ��� �����
    //  fout.close();
    //  cerr << "������������ �������� ���� ��� ����� �����." << endl;
    //  cout << "������� ���� � �����: ";
    //  getline(cin, pathOutput);
    //  fout.open(pathOutput);
    //}

  cout << endl;
  fout.close();
  while (fout) { // ���� ���� ��� ����������
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
      switch (saveContext) {
      case SaveResultContext: {  // ���������� �����������
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, saveContext);
        break; }
      case SaveInitialDataContext: { // ���������� �������� ������
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, saveContext);
        break; }
      }
      break;
    }

    case SavingMenuItems::GoBackMenuItem: { // ������� ����� �������
      PrintMenu();
      break; }
    }
    break;
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