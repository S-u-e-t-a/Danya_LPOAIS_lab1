#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
#include "exceptions.h"
#include "tests.h"

using namespace std;

void MenuInputCheck(int* userChoice, int min, int max) { // �������� ������� �����. ��������� ������� ������ �����
  if (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) {
    cin.clear();
    cout << endl;
    cerr << "������� ������������ ��������.";
    cout << endl;
    cout << "������� ��������: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    MenuInputCheck(userChoice, min, max);
  }
}

void Greeting() { // ����������
  system("cls");
  cout << "������������ ������ �1" << endl;
  cout << "������� 5" << endl;
  cout << endl;
  cout << "������ ��������� ���������� ����� ���� ���� � ������, ���������� �������� ������." << endl;
  cout << "���� ������ ����� ����������� ������� ��� ������ ���� ������� .txt." << endl;
  cout << "� ��������� ����������� ������� ���������� �������� ������ �" << endl;
  cout << "����������� ������ ��������� � ���� �������.txt." << endl;
  cout << endl;
  cout << "�����: ������� ������" << endl;
  cout << "������: 494" << endl;
  cout << endl;
  system("pause");
}

void PrintMenu() {
  system("cls");
  cout << "\t������� ����" << endl;
  cout << "�������� �������:" << endl;
  cout << "1. ������ ����� �������." << endl;
  cout << "2. ������� ����� �� �����." << endl;
  cout << "3. ������� ���������� � ��������� � ������." << endl;
  cout << "4. ��������� ��������� ������������." << endl;
  cout << "5. ����� �� ���������." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintYesNoMenu(const string msg) {
  cout << msg << endl;
  cout << "1 - �� | 2 - ���" << endl;
  cout << endl;
  cout << "�����: ";
}

void PrintErrorMenu() { // ��������������� ����, ���� � ���� �������� �������� ��������� ������
  system("cls");
  cout << "\t��� �� ������ �������?" << endl;
  cout << "1. ������ ������ ������." << endl;
  cout << "2. ��������� � ������� ����." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintText(const vector<string>& text, const string& searchSymbol) {
  cout << "��� �����:" << endl;
  cout << endl;
  for (int i = 0; i < text.size(); i++) {
    cout << text[i] << endl;
  }
  cout << endl;
  cout << "������ ������: " << searchSymbol;
  cout << endl;
}

void PrintResult(const vector<string>& wordsWithSearchSymbol) {
  cout << "��������� ������:" << endl;
  cout << endl;
  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    cout << wordsWithSearchSymbol[i] << endl;
  }
  cout << endl;
}

int ManualInput(vector<string>& text, string& searchSymbol) {
  string buffer;
  system("cls");
  cout << "������� �����." << endl;
  cout << "�� ��������� ����� ������� ������ ������." << endl;
  cout << endl;
  getline(cin, buffer);
  while (true) {
    getline(cin, buffer);
    if (buffer != "") {
      text.push_back(buffer);
    }
    else {
      if (text.size() == 0) {
        cout << "�� �� ����� �����." << endl;
        cout << "������� �����." << endl;
      }
      else {
        break;
      }
    }
  }
  cout << "������� ������ ��� ������: ";
  cin >> searchSymbol;
  return NoError;
}

int SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol) {
  int userChoice;
  int res;
  PrintYesNoMenu("��������� ��������� � ����?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
    // ��� ��� ������ ��������� �������
  case Yes: {
    res = SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveResultContext);
    if (res == ErrorInFileFuncs) {
      return ErrorInFileFuncs;
    }
    break;
  }
  case No: { break; }
  }

  cout << endl;
  PrintYesNoMenu("��������� �������� ������ � ����?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: {
    res = SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveInitialDataContext);
    if (res == ErrorInFileFuncs) {
      return ErrorInFileFuncs;
    }
    break;
  }
  case No: { break; }
  }
  return NoError;
}

void Menu() { // ������� ����
  int userChoice;
  int res;
  vector<string> text;
  vector<string> wordsWithSearchSymbol;
  string searchSymbol;
  PrintMenu();
  MenuInputCheck(&userChoice, ManualInputMenuItem, ExitMenuItem);
  cout << endl;
  switch (userChoice) {
  case ManualInputMenuItem: {
    res = ManualInput(text, searchSymbol);
    system("cls");
    break;
  }
  case InputFromFileMenuItem: {
    res = FileInput(text, searchSymbol);
    break; }
  case ShowInfoMenuItem: {Greeting(); Menu(); break; }
  case UnitTestMenuItem: {RunModuleTests(); Menu(); break; }
  case ExitMenuItem: {cout << "��������� ���������." << endl; exit(0); }
  }

  if (res == NoError) { // ���� ��� ����� �� ��������� ������
    PrintText(text, searchSymbol);
    SplitText(text, wordsWithSearchSymbol);
    FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
    PrintResult(wordsWithSearchSymbol);
    res = SaveData(text, wordsWithSearchSymbol, searchSymbol);
    if (res == NoError) {
      Menu();
    }
    else {
      system("pause");
    }
  }
}

