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
      throw WrongChoiceException("������� ������������ ��������.", userChoice, min, max);
      //MenuInputCheck(userChoice, min, max);
    }
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

void ManualInput(vector<string>& text, string& searchSymbol) { // �� ���� ����������
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
}

void SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol) {
  int userChoice;
  PrintYesNoMenu("��������� ��������� � ����?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveResultContext); break; }
  case No: { break; }
  }
  cout << endl;
  PrintYesNoMenu("��������� �������� ������ � ����?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveInitialDataContext); break; }
  case No: { break; }
  }
}

void Menu() { // ������� ����
  int userChoice;
  vector<string> text;
  vector<string> wordsWithSearchSymbol;
  string searchSymbol;
  try {
    PrintMenu();
    MenuInputCheck(&userChoice, ManualInputMenuItem, ExitMenuItem);
    cout << endl;
    switch (userChoice) {
    case ManualInputMenuItem: {
      ManualInput(text, searchSymbol);
      SplitText(text, wordsWithSearchSymbol);
      FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
      PrintResult(wordsWithSearchSymbol);
      SaveData(text, wordsWithSearchSymbol, searchSymbol);
      break;
    }
    case InputFromFileMenuItem: {
      FileInput(text, searchSymbol);
      PrintText(text, searchSymbol);
      SplitText(text, wordsWithSearchSymbol);
      FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
      PrintResult(wordsWithSearchSymbol);
      SaveData(text, wordsWithSearchSymbol, searchSymbol);
      break; }
    case ShowInfoMenuItem: {Greeting(); Menu(); break; }
                         //case UnitTestMenuItem: {Module_Test(); Menu(); break; }
    case ExitMenuItem: {cout << "��������� ���������." << endl; exit(0); }
    }
  }
  catch (WrongChoiceException& ex)
  {
    cout << endl;
    cerr << "������: " << ex.what() << endl;
    cout << "�������� �����: " << *(ex.GetDataState()) << endl; // ���� ������ �����, �� ��� ������� 0
    MenuInputCheck(ex.GetDataState(), ex.GetMin(), ex.GetMax());
  }
  catch (WrongPathInput& ex)
  {
    cout << endl;
    cerr << "������: " << ex.what() << endl;
    cout << "�������� �����: " << ex.GetDataState() << endl;
    cout << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
      
      // ����������� ����� ������ ������ ������ ������ ������ ���������� ( ����� ���� ������ ������� PathInput)
      switch (ex.GetContext()) { // ����� ������, � ������� ��������� ����������
      case SaveResultContext: {
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
        break; }
      case SaveInitialDataContext: {
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
        break; }
      case InputContext: {
        FileInput(text, searchSymbol);
        PrintText(text, searchSymbol);
        SplitText(text, wordsWithSearchSymbol);
        FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
        PrintResult(wordsWithSearchSymbol);
        SaveData(text, wordsWithSearchSymbol, searchSymbol);
        break; }
      }
    }
     break;
    case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
      PrintMenu();
      break; }
    }
  }
  catch (FileIsReadOnly& ex)
  {
    cout << endl;
    cerr << "������: " << ex.what() << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
      SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      break; }
    case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
      PrintMenu();
      break; }
    }
  }
}