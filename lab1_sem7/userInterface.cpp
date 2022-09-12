#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
#include "exceptions.h"
//#include "module_test.h"

using namespace std;

void MenuInputCheck(int* userChoice, int min, int max) { // Проверка ручного ввода. Позволяет вводить только числа
  bool choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if ((cin >> *userChoice).good() && *userChoice >= min && *userChoice <= max) {
      choiceIsCorrect = true;
    }
    else {
      throw WrongChoiceException("Введено неправильное значение.", userChoice, min, max);
      //MenuInputCheck(userChoice, min, max);
    }
  }
}

void Greeting() { // Приветсвие
  system("cls");
  //cout << "Эта программа копирует строки, " << endl;
  //cout << "подсчитывает количество символов, слов, строк, абзацев в тексте." << endl;
  //cout << "Производит поиск заданной подстроки в тексте и подсчитывает число вхождений." << endl;
  cout << endl;
  cout << "Автор: Ермаков Даниил" << endl;
  cout << "Группа: 494" << endl;
  cout << "Лабораторная работа №4" << endl;
  cout << "Вариант 5" << endl;
  cout << endl;
}

void PrintMenu() {
  system("cls");
  cout << "\tГЛАВНОЕ МЕНЮ" << endl;
  cout << "Выберите вариант:" << endl;
  cout << "1. Ввести текст вручную." << endl;
  cout << "2. Вывести текст из файла." << endl;
  cout << "3. Вывести информацию о программе и авторе." << endl;
  cout << "4. Запустить модульное тестирование." << endl;
  cout << "5. Выйти из программы." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintYesNoMenu(string& msg) {
  cout << msg << endl;
  cout << "1 - Да | 2 - Нет" << endl;
  cout << endl;
  cout << "Выбор: ";
}

void PrintErrorMenu() { // Вспомогательное меню, если в ходе указания значений произошла ошибка
  system("cls");
  cout << "\tЧто вы хотите сделать?" << endl;
  cout << "1. Ввести данные заново." << endl;
  cout << "2. Назад." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintTextFromFile(vector<string>& text, string& searchSymbol) {
  cout << "Ваш текст:" << endl;
  cout << endl;
  for (int i = 0; i < text.size(); i++) {
    cout << text[i] << endl;
  }
  cout << "Символ поиска: " << searchSymbol;
  cout << endl;
}

void ManualInput(vector<string>& text, string& searchSymbol) {
  string buffer;
  system("cls");
  cout << "Введите текст." << endl;
  cout << "По окончании ввода введите пустую строку." << endl;
  cout << endl;
  while (true) {
    getline(cin, buffer);
    if (buffer != "") {
      text.push_back(buffer);
    }
    else {
      if (text.size() == 0) {
        cout << "Вы не ввели текст." << endl;
        cout << "Введите текст." << endl;
      }
      else {
        break;
      }
    }
  }
  cout << "Введите символ для поиска: ";
  cin >> searchSymbol;
}

void SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol) {
  int userChoice;
  PrintYesNoMenu("Сохранить результат в файл?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveResultContext); break; }
  case No: { break; }
  }
  //cout << endl;
  PrintYesNoMenu("Сохранить исходные данные в файл?");
  MenuInputCheck(&userChoice, Yes, No);
  switch (userChoice) {
  case Yes: { SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveInitialDataContext); break; }
  case No: { break; }
  }
}

void Menu() { // Главное меню
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
      // Вызов метода для поиска, а в нём SaveData
      break;
    }
    case InputFromFileMenuItem: {
      // УЗНАТЬ КАК ВЕРНУТЬ СТРОКУ С СИМВОЛОМ ЧЕРЕЗ УКАЗАТЕЛЬ
      FileInput(text, searchSymbol);
      PrintTextFromFile(text, searchSymbol);
      wordsWithSearchSymbol = text;
      
      // Вызов метода для поиска, а в нём SaveData


      break; }
    case ShowInfoMenuItem: {Greeting(); Menu(); break; }
                         //case UnitTestMenuItem: {Module_Test(); Menu(); break; }
    case ExitMenuItem: {cout << "Программа завершена." << endl; exit(0); }
    }
  }
  catch (WrongChoiceException& ex)
  {
    cerr << "Ошибка: " << ex.what() << endl;
    cout << "Значение ввода: " << *(ex.GetDataState()) << endl;
    MenuInputCheck(ex.GetDataState(), ex.GetMin(), ex.GetMax());
  }
  catch (WrongPathInput& ex)
  {
    cerr << "Ошибка: " << ex.what() << endl;
    cout << "Значение ввода: " << ex.GetDataState() << endl;
    cout << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
      
      // ПОПРОБОВАТЬ НАЙТИ СПОСОБ ПРОСТО УЗНАТЬ ОТКУДА ПРИШЛО ИСКЛЮЧЕНИЕ ( ТОГДА НАДО УБРАТЬ ФУНКЦИЮ PathInput)
      switch (ex.GetContext()) { // Вызов метода, в котором произошло исключение
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
        // Вызов метода для поиска, а в нём SaveData
        break; }
      }
    }
     break;
    case ErrorMenuItems::GoBackMenuItem: { // Вариант выйти обратно
      PrintMenu();
      break; }
    }
  }
  catch (FileIsReadOnly& ex)
  {
    cerr << "Ошибка: " << ex.what() << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
      SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      break; }
    case ErrorMenuItems::GoBackMenuItem: { // Вариант выйти обратно
      PrintMenu();
      break; }
    }
  }
}