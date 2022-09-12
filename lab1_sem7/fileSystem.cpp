#include "fileSystem.h"
#include "userInterface.h"
#include "exceptions.h"
#include <Windows.h>

using namespace std::experimental::filesystem;
using namespace std;

void CheckPath(string filename) { // Проверка пути
  size_t found = filename.find_last_of("\\");
  size_t point = filename.find_last_of(".");
  size_t base = point - found - 1;
  string baseFilenameStr = filename.substr(found + 1, base);
  const char* basefilenameChar = baseFilenameStr.c_str();
  ofstream file(filename, ios::app);
  if (!_strcmpi(basefilenameChar, "con")) {
    file.close(); // мб не надо
    throw WrongPathInput("Некорректное указание пути или имени файла.", filename);
  }
  if (!std::filesystem::is_regular_file(filename)) {
    file.close(); // мб не надо
    throw WrongPathInput("Некорректное указание пути или имени файла.", filename);
  }
  file.close();

  //throw WrongPathInput("Некорректное указание пути или имени файла.", filename); // ТОГДА ФУНКЦИЯ VOID а не BOOL

  //return false;
}

void CheckReadOnly(string filename) { // Проверка файла на атрибут "только для чтения"
  ifstream file(filename);
  WIN32_FIND_DATAA findData;
  LPCSTR name = filename.c_str();
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    cerr << "Невозможно сохранить данные в файл, предназначенный только для чтения." << endl;
    throw FileIsReadOnly("Невозможно сохранить данные в файл, предназначенный только для чтения."); // ТОГДА ФУНКЦИЯ VOID а не BOOL
    //return false;
  }
  //else return true;
}

void PrintAdditionalMenu() { // Вспомогательное меню, если в ходе сохранения файла был обнаружен уже существующий файл
  system("cls");
  cout << "Данный файл уже существует." << endl;
  cout << endl;
  cout << "\tЧто вы хотите сделать?" << endl;
  cout << "1. Перезаписать файл." << endl;
  cout << "2. Создать новый файл." << endl;
  cout << "3. Назад." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintErrorMenu() { // Вспомогательное меню, если в ходе указания значений произошла ошибка
  system("cls");
  cout << "\tЧто вы хотите сделать?" << endl;
  cout << "1. Ввести данные заново." << endl;
  cout << "2. Назад." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, string path) { // Вспомогательная функция для записи данных в файл
  ofstream fout(path);
  fout << "Исходный текст: " << endl;
  fout << endl;
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
  fout << endl;
  fout << "Символ поиска: " << searchSymbol << endl;
  fout << endl;
  //if (text != wordsWithSearchSymbol) {
  fout << "Слова, имеющие данный символ: " << endl;
  fout << endl;
  for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
    fout << wordsWithSearchSymbol[i] << endl;
    //}
    fout << endl;
  }
}

void PrintInitialData(const vector<string>& text, string path) { // Функция для записи исходных данных в файл
  ofstream fout(path);
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
}

void FileInput(vector<string>& text) { // Функция для чтения данных из файла
  system("cls");
  text.clear();
  string pathInput;
  cout << "Введите путь к файлу: ";
  getline(cin, pathInput);

  //CheckPath(pathInput) Если исключение внутри, то тут вызов

  ifstream fin(pathInput);

  //if (!fin || CheckPath(pathInput)) { // Проверка на существование файла по указанному пути
  //  fin.close();

    //throw WrongPathInput("Некорректное указание пути или имени файла.\n", pathInput);

    //catch (WrongPathInput &ex) // в try catch засунусть
    //{
    //  cerr << "Ошибка: " << ex.what() << endl;
    //  cout << "Значение ввода: " << ex.GetDataState() << endl;
    //  cout << endl;
    //  int userChoice;
    //  PrintErrorMenu();
    //  MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
    //switch (userChoice) {
    //case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
    //  FileInput(vector<string>& text);
    //  break; }
    //case ErrorMenuItems::GoBackMenuItem: { // Вариант выйти обратно
    //  PrintMenu();
    //  break; }
    //}
  //}

  // СТАРОЕ
  //while (true) {
  //  while (!fin || CheckPath(pathInput)) { // Проверка на существование файла по указанному пути
  //    
  //    PrintErrorMenu();
  //    getline(cin, pathInput);
  //    fin.open(pathInput); // Открытие файла
  //    cout << endl;
  //  }
  //  break;
  //}

  fin.seekg(0, ios::beg);
  string temp; // Переменная для временного хранения символов из файла
  while (!fin.eof()) {
    while (getline(fin, temp))
      text.push_back(temp);
  }
  fin.close();
}

void SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, int saveContext) { // Функция для создания файлов с результатами или исоходными данными
  string pathOutput;
  int userChoice;
  cout << "Введите путь к файлу: ";
  getline(cin, pathOutput);
  //CheckPath(pathOutput) Если исключение внутри, то тут вызов
  //CheckReadOnly(pathOutput) Если исключение внутри, то тут вызов
  ifstream fout(pathOutput);

  //if (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // Проверка на корректный путь и имя файла
  //  throw WrongPathInput("Некорректное указание пути или имени файла.\n", pathInput);

  //  catch (WrongPathInput& ex) // в try catch засунусть
  //  {
  //    cerr << "Ошибка: " << ex.what() << endl;
  //    cout << "Значение ввода: " << ex.GetDataState() << endl;
  //    cout << endl;
  //    int userChoice;
  //    PrintErrorMenu();
  //    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, ErrorMenuItems::GoBackMenuItem);
  //    switch (userChoice) {
  //    case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
  //      FileInput(vector<string>&text);
  //      break; }
  //    case ErrorMenuItems::GoBackMenuItem: { // Вариант выйти обратно
  //      PrintMenu();
  //      break; }
  //    }
  //  }
  
    // СТАРОЕ
    //while (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // Проверка на корректный путь и имя файла
    //  fout.close();
    //  cerr << "Некорректное указание пути или имени файла." << endl;
    //  cout << "Введите путь к файлу: ";
    //  getline(cin, pathOutput);
    //  fout.open(pathOutput);
    //}

  cout << endl;
  fout.close();
  while (fout) { // Если файл уже существует
    PrintAdditionalMenu(); // Вывод вспомогательного меню
    MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
    switch (userChoice) {
    case RewriteMenuItem: { // Вариант с перезаписью
      ofstream fout(pathOutput);
      switch (saveContext) {
      case SaveResultContext: { // Сохранение результатов
        PrintResult(text, wordsWithSearchSymbol, searchSymbol, pathOutput);
        fout.close();
        break; }
      case SaveInitialDataContext: { // Сохранение исходных данных
        fout.close();
        PrintInitialData(text, pathOutput);
        break; }
      }
      break;
    }
    case CreateNewFileMenuItem: { // Вариант с созданием нового файла
      fout.close();
      switch (saveContext) {
      case SaveResultContext: {  // Сохранение результатов
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, saveContext);
        break; }
      case SaveInitialDataContext: { // Сохранение исходных данных
        SaveFile(text, wordsWithSearchSymbol, searchSymbol, saveContext);
        break; }
      }
      break;
    }

    case SavingMenuItems::GoBackMenuItem: { // Вариант выйти обратно
      PrintMenu();
      break; }
    }
    break;
  }
  if (!fout) { // Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
    switch (saveContext) {
    case SaveResultContext: {
      PrintResult(text, wordsWithSearchSymbol, searchSymbol, pathOutput);
      break; }
    case SaveInitialDataContext: {
      PrintInitialData(text, pathOutput);
      break; }
    }
    fout.close();
  }
}