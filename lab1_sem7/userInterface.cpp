#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
//#include "module_test.h"

using namespace std;

// проверка на ввод числа и выбор числа

int MenuInputCheck() { // Проверка ручного ввода. Позволяет вводить только числа
  int correctValue = 0;
  cin >> correctValue;
  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  while (cin.fail()) {
    cin.clear();
    cout << "Ввод некорректен, попробуйте снова: ";
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> correctValue;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  };
  return correctValue;
}

void SaveData(const vector<string>& text, const vector<string>& redacted_text, string line_for_search, int counter) {
  cout << "Сохранить результат в файл?" << endl;
  cout << "1 - Да | 2 - Нет" << endl;
  int choice = InputCheck();
  bool choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if (choice >= Yes && choice <= No) {
      choiceIsCorrect = true;
    }
    else {
      cerr << "Введено неправильное значение, попробуйте снова: ";
      choice = InputCheck();
    }
  }
  switch (choice) {
  case Yes: { /*File_Output_With_Result(text, redacted_text, stats, line_for_search, counter);*/ break; }
  case No: { break; }
  }
  cout << endl;
  cout << "Сохранить исходные данные в файл?" << endl;
  cout << "1 - Да | 2 - Нет" << endl;
  choice = InputCheck();
  choiceIsCorrect = false;
  while (choiceIsCorrect == false) {
    if (choice >= Yes && choice <= No) {
      choiceIsCorrect = true;
    }
    else {
      cerr << "Введено неправильное значение, попробуйте снова: ";
      choice = InputCheck();
    }
  }
  switch (choice) {
  case Yes: { SaveInitialData(text); break; }
  case No: { break; }
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


void Menu() { // Главное меню
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
      cerr << "Введено неправильное значение, попробуйте снова: ";
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
  case ExitMenuItem: {cout << "Программа завершена. До свидания." << endl; exit(0); }
  }
}