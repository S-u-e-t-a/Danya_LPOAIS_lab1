#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
//#include "module_test.h"

using namespace std;

// �������� �� ���� ����� � ����� �����

int MenuInputCheck() { // �������� ������� �����. ��������� ������� ������ �����
  int correctValue = 0;
  cin >> correctValue;
  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  while (cin.fail()) {
    cin.clear();
    cout << "���� �����������, ���������� �����: ";
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> correctValue;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  };
  return correctValue;
}

void SaveData(const vector<string>& text, const vector<string>& redacted_text, string line_for_search, int counter) {
  cout << "��������� ��������� � ����?" << endl;
  cout << "1 - �� | 2 - ���" << endl;
  int choice = InputCheck();
  bool choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if (choice >= Yes && choice <= No) {
      choiceIsCorrect = true;
    }
    else {
      cerr << "������� ������������ ��������, ���������� �����: ";
      choice = InputCheck();
    }
  }
  switch (choice) {
  case Yes: { /*File_Output_With_Result(text, redacted_text, stats, line_for_search, counter);*/ break; }
  case No: { break; }
  }
  cout << endl;
  cout << "��������� �������� ������ � ����?" << endl;
  cout << "1 - �� | 2 - ���" << endl;
  choice = InputCheck();
  choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if (choice >= Yes && choice <= No) {
      choiceIsCorrect = true;
    }
    else {
      cerr << "������� ������������ ��������, ���������� �����: ";
      choice = InputCheck();
    }
  }
  switch (choice) {
  case Yes: { SaveInitialData(text); break; }
  case No: { break; }
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


void Menu() { // ������� ����
  int variant;
  //amount_in_text stats = {};
  vector<string> text;
  vector<string> wordsWithSearchSymbol;
  char searchSymbol;
  int counter = 0;
  PrintMenu();
  variant = MenuInputCheck();

  bool variant_is_correct = false;
  while (variant_is_correct == false) {
    if (variant >= ManualInputMenuItem && variant <= ExitMenuItem) {
      variant_is_correct = true;
    }
    else {
      cerr << "������� ������������ ��������, ���������� �����: ";
      variant = InputCheck();
    }
  }
  cout << endl;
  switch (variant) {
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
  case ExitMenuItem: {cout << "��������� ���������. �� ��������." << endl; exit(0); }
  }
}