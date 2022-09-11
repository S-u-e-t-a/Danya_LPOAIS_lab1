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
      throw WrongChoiceException("Введено неправильное значение.\n", *userChoice);

      //catch (WrongChoiceException &ex) // в try catch засунусть
      //{
      //  cout << "Ошибка: " << ex.what() << endl;
      //  cout << "Значение ввода: " << ex.GetDataState() << endl;
      //}

      cerr << "Введено неправильное значение, попробуйте снова: ";
      MenuInputCheck(userChoice, min, max);
    }
  }
}

void Greeting() { // Приветсвие
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
  cout << "\tMENU" << endl;
  cout << "Выберите вариант:" << endl;
  cout << "1. Ввести текст вручную." << endl;
  cout << "2. Вывести текст из файла." << endl;
  cout << "3. Вывести информацию о программе и авторе." << endl;
  cout << "4. Запустить модульное тестирование." << endl;
  cout << "5. Выйти из программы." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintSaveMenu(int saveContext) {
  switch (saveContext) {
  case SaveResultContext: {   cout << "Сохранить результат в файл?" << endl; break; }
  case SaveInitialDataContext: {   cout << "Сохранить исходные данные в файл?" << endl; break; }
  }
  cout << "1 - Да | 2 - Нет" << endl;
  cout << endl;
  cout << "Выбор: ";
}

void ManualInput(vector<string> text, char* searchSymbol) {
  string buffer;
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

void Menu() { // Главное меню
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
    cout << "Ваш текст:" << endl;
    cout << endl;
    for (int i = 0; i < text.size(); i++) {
      cout << text[i] << endl;
    }
    cout << "Символ поиска: " << searchSymbol;
    wordsWithSearchSymbol = text;
    cout << endl;
    break; }
  case ShowInfoMenuItem: {Greeting(); Menu(); break; }
                       //case UnitTestMenuItem: {Module_Test(); Menu(); break; }
  case ExitMenuItem: {cout << "Программа завершена." << endl; exit(0); }
  }
}