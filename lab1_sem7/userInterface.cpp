#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
#include "exceptions.h"
//#include "module_test.h"

using namespace std;

void MenuInputCheck(int* userChoice, int min, int max) { // �������� ������� �����. ��������� ������� ������ �����
  bool choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if ((cin >> *userChoice).good() && *userChoice >= min && *userChoice <= max) {
      choiceIsCorrect = true;
    }
    else {
      throw WrongChoiceException("������� ������������ ��������.\n", *userChoice);

      //catch (WrongChoiceException &ex) // � try catch ���������
      //{
      //  cout << "������: " << ex.what() << endl;
      //  cout << "�������� �����: " << ex.GetDataState() << endl;
      //}

      cerr << "������� ������������ ��������, ���������� �����: ";
      MenuInputCheck(userChoice, min, max);
    }
  }
}

void Greeting() { // ����������
  //cout << "��� ��������� �������� ������, " << endl;
  //cout << "������������ ���������� ��������, ����, �����, ������� � ������." << endl;
  //cout << "���������� ����� �������� ��������� � ������ � ������������ ����� ���������." << endl;
  cout << endl;
  cout << "�����: ������� ������" << endl;
  cout << "������: 494" << endl;
  cout << "������������ ������ �4" << endl;
  cout << "������� 5" << endl;
  cout << endl;
}

void PrintMenu() {
  cout << "\tMENU" << endl;
  cout << "�������� �������:" << endl;
  cout << "1. ������ ����� �������." << endl;
  cout << "2. ������� ����� �� �����." << endl;
  cout << "3. ������� ���������� � ��������� � ������." << endl;
  cout << "4. ��������� ��������� ������������." << endl;
  cout << "5. ����� �� ���������." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintSaveMenu(int saveContext) {
  switch (saveContext) {
  case SaveResultContext: {   cout << "��������� ��������� � ����?" << endl; break; }
  case SaveInitialDataContext: {   cout << "��������� �������� ������ � ����?" << endl; break; }
  }
  cout << "1 - �� | 2 - ���" << endl;
  cout << endl;
  cout << "�����: ";
}

void ManualInput(vector<string> text, char* searchSymbol) {
  string buffer;
  cout << "������� �����." << endl;
  cout << "�� ��������� ����� ������� ������ ������." << endl;
  cout << endl;
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
}

void SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol) {
  int userChoice;
  PrintSaveMenu(SaveResultContext);
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveResult(text, wordsWithSearchSymbol, searchSymbol); break; }
  case No: { break; }
  }
  //cout << endl;
  PrintSaveMenu(SaveInitialDataContext);
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveInitialData(text); break; }
  case No: { break; }
  }
}

void Menu() { // ������� ����
  int userChoice;
  vector<string> text;
  vector<string> wordsWithSearchSymbol;
  char searchSymbol;

  PrintMenu();
  MenuInputCheck(&userChoice, ManualInputMenuItem, ExitMenuItem);

  cout << endl;
  switch (userChoice) {
  case ManualInputMenuItem: {
    ManualInput(text, &searchSymbol);
    break;
  }
  case InputFromFileMenuItem: {
    text = FileInput(text);
    cout << "��� �����:" << endl;
    cout << endl;
    for (int i = 0; i < text.size(); i++) {
      cout << text[i] << endl;
    }
    cout << "������ ������: " << searchSymbol;
    wordsWithSearchSymbol = text;
    cout << endl;
    break; }
  case ShowInfoMenuItem: {Greeting(); Menu(); break; }
                       //case UnitTestMenuItem: {Module_Test(); Menu(); break; }
  case ExitMenuItem: {cout << "��������� ���������." << endl; exit(0); }
  }
}