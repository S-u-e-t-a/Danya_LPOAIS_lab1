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

void PrintYesNoMenu(string& msg) {
  cout << msg << endl;
  cout << "1 - �� | 2 - ���" << endl;
  cout << endl;
  cout << "�����: ";
}

void PrintErrorMenu() { // ��������������� ����, ���� � ���� �������� �������� ��������� ������
  system("cls");
  cout << "\t��� �� ������ �������?" << endl;
  cout << "1. ������ ������ ������." << endl;
  cout << "2. �����." << endl;
  cout << endl;
  cout << "�������� ����� ����: ";
}

void PrintTextFromFile(vector<string>& text, string& searchSymbol) {
  cout << "��� �����:" << endl;
  cout << endl;
  for (int i = 0; i < text.size(); i++) {
    cout << text[i] << endl;
  }
  cout << "������ ������: " << searchSymbol;
  cout << endl;
}

void ManualInput(vector<string>& text, string& searchSymbol) {
  string buffer;
  system("cls");
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

void SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol) {
  int userChoice;
  PrintYesNoMenu("��������� ��������� � ����?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveResultContext); break; }
  case No: { break; }
  }
  //cout << endl;
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
      // ����� ������ ��� ������, � � �� SaveData
      break;
    }
    case InputFromFileMenuItem: {
      // ������ ��� ������� ������ � �������� ����� ���������
      FileInput(text, searchSymbol);
      PrintTextFromFile(text, searchSymbol);
      wordsWithSearchSymbol = text;
      
      // ����� ������ ��� ������, � � �� SaveData


      break; }
    case ShowInfoMenuItem: {Greeting(); Menu(); break; }
                         //case UnitTestMenuItem: {Module_Test(); Menu(); break; }
    case ExitMenuItem: {cout << "��������� ���������." << endl; exit(0); }
    }
  }
  catch (WrongChoiceException& ex)
  {
    cerr << "������: " << ex.what() << endl;
    cout << "�������� �����: " << *(ex.GetDataState()) << endl;
    MenuInputCheck(ex.GetDataState(), ex.GetMin(), ex.GetMax());
  }
  catch (WrongPathInput& ex)
  {
    cerr << "������: " << ex.what() << endl;
    cout << "�������� �����: " << ex.GetDataState() << endl;
    cout << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
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
        PrintTextFromFile(text, searchSymbol);
        wordsWithSearchSymbol = text;
        cout << endl;
        // ����� ������ ��� ������, � � �� SaveData
        break; }
      }
    }
     break;
    case ErrorMenuItems::GoBackMenuItem: { // ������� ����� �������
      PrintMenu();
      break; }
    }
  }
  catch (FileIsReadOnly& ex)
  {
    cerr << "������: " << ex.what() << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
      SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      break; }
    case ErrorMenuItems::GoBackMenuItem: { // ������� ����� �������
      PrintMenu();
      break; }
    }
  }
}