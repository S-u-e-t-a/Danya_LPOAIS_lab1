#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
//#include "module_test.h"

using namespace std;

void MenuInputCheck(int *userChoice, int min, int max) { // �������� ������� �����. ��������� ������� ������ �����
  bool choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if ((cin >> *userChoice).good() && *userChoice >= min && *userChoice <= max) {
      choiceIsCorrect = true;
    }
    else {
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

//void Save_Data(const vector<string>& text, const vector<string>& redacted_text, amount_in_text stats, string line_for_search, int counter) {
//  cout << "��������� ��������� � ����?" << endl;
//  cout << "1 - �� | 2 - ���" << endl;
//  int choice = Input_Check();
//  bool choice_is_correct = false;
//  while (choice_is_correct == false) {
//    if (choice >= Yes && choice <= No) {
//      choice_is_correct = true;
//    }
//    else {
//      cerr << "������� ������������ ��������, ���������� �����: ";
//      choice = Input_Check();
//    }
//  }
//  switch (choice) {
//  case Yes: { File_Output_With_Result(text, redacted_text, stats, line_for_search, counter); break; }
//  case No: { break; }
//  }
//  cout << endl;
//  cout << "��������� �������� ������ � ����?" << endl;
//  cout << "1 - �� | 2 - ���" << endl;
//  choice = Input_Check();
//  choice_is_correct = false;
//  while (choice_is_correct == false) {
//    if (choice >= Yes && choice <= No) {
//      choice_is_correct = true;
//    }
//    else {
//      cerr << "������� ������������ ��������, ���������� �����: ";
//      choice = Input_Check();
//    }
//  }
//  switch (choice) {
//  case Yes: { File_Output_Initial_Data(text); break; }
//  case No: { break; }
//  }
//}

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