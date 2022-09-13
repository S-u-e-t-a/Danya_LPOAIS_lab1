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
  cout << "Лабораторная работа №1" << endl;
  cout << "Вариант 5" << endl;
  cout << endl;
  cout << "Данная программа производит поиск всех слов в тексте, содержащих заданный символ." << endl;
  cout << "Ввод данных можно осуществить вручную или открыв файл формата .txt." << endl;
  cout << "В программе реализованы функции сохранения исходных данных и" << endl;
  cout << "результатов работы программы в файл формата.txt." << endl;
  cout << endl;
  cout << "Автор: Ермаков Даниил" << endl;
  cout << "Группа: 494" << endl;
  cout << endl;
  system("pause");
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

void PrintYesNoMenu(const string msg) {
  cout << msg << endl;
  cout << "1 - Да | 2 - Нет" << endl;
  cout << endl;
  cout << "Выбор: ";
}

void PrintErrorMenu() { // Вспомогательное меню, если в ходе указания значений произошла ошибка
  system("cls");
  cout << "\tЧто вы хотите сделать?" << endl;
  cout << "1. Ввести данные заново." << endl;
  cout << "2. Вернуться в главное меню." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintText(const vector<string>& text, const string& searchSymbol) {
  cout << "Ваш текст:" << endl;
  cout << endl;
  for (int i = 0; i < text.size(); i++) {
    cout << text[i] << endl;
  }
  cout << "Символ поиска: " << searchSymbol;
  cout << endl;
}

void PrintResult(const vector<string>& wordsWithSearchSymbol) {
  cout << "Результат поиска:" << endl;
  cout << endl;
  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    cout << wordsWithSearchSymbol[i] << endl;
  }
  cout << endl;
}

void ManualInput(vector<string>& text, string& searchSymbol) { // мб сюда исключение
  string buffer;
  system("cls");
  cout << "Введите текст." << endl;
  cout << "По окончании ввода введите пустую строку." << endl;
  cout << endl;
  getline(cin, buffer);
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
  cout << endl;
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
    case ExitMenuItem: {cout << "Программа завершена." << endl; exit(0); }
    }
  }
  catch (WrongChoiceException& ex)
  {
    cout << endl;
    cerr << "Ошибка: " << ex.what() << endl;
    cout << "Значение ввода: " << *(ex.GetDataState()) << endl; // Если ввести букву, то тут выведет 0
    MenuInputCheck(ex.GetDataState(), ex.GetMin(), ex.GetMax());
  }
  catch (WrongPathInput& ex)
  {
    cout << endl;
    cerr << "Ошибка: " << ex.what() << endl;
    cout << "Значение ввода: " << ex.GetDataState() << endl;
    cout << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
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
        PrintText(text, searchSymbol);
        SplitText(text, wordsWithSearchSymbol);
        FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
        PrintResult(wordsWithSearchSymbol);
        SaveData(text, wordsWithSearchSymbol, searchSymbol);
        break; }
      }
    }
     break;
    case GoBackToMainMenuMenuItem: { // Вариант выйти в главное меню
      PrintMenu();
      break; }
    }
  }
  catch (FileIsReadOnly& ex)
  {
    cout << endl;
    cerr << "Ошибка: " << ex.what() << endl;
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
      SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      break; }
    case GoBackToMainMenuMenuItem: { // Вариант выйти в главное меню
      PrintMenu();
      break; }
    }
  }
}