#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

using namespace std::experimental::filesystem;
using namespace std;

bool CheckPath(string filename) { // Проверка пути
  size_t found = filename.find_last_of("\\");
  size_t point = filename.find_last_of(".");
  size_t base = point - found - 1;
  string baseFilenameStr = filename.substr(found + 1, base);
  const char* basefilenameChar = baseFilenameStr.c_str();
  ofstream file(filename, ios::app);
  if (!_strcmpi(basefilenameChar, "con")) return true;
  //if (!is_regular_file(filename)) return true;
  file.close();
  return false;
}

bool CheckReadOnly(string filename) { // Проверка файла на атрибут "только для чтения"
  ifstream file(filename);
  WIN32_FIND_DATAA findData;
  LPCSTR name = filename.c_str();
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    cerr << "Невозможно сохранить данные в файл, предназначенный только для чтения." << endl;
    return false;
  }
  else return true;
}

void PrintAdditionalMenu() { // Вспомогательное меню, если в ходе сохранения файла был обнаружен уже существующий файл. Предлагает перезаписать файл или создать другой файл с новым именем
  cout << "Данный файл уже существует." << endl;
  cout << endl;
  cout << "\tЧто вы хотите сделать?" << endl;
  cout << "1. Перезаписать файл." << endl;
  cout << "2. Создать новый файл." << endl;
  cout << "3. Назад." << endl;
}

void PrintResult(const vector<string>& text, const vector<string>& redacted_text, string line_for_search, string path) { // Вспомогательная функция для записи данных в файл
  ofstream fout(path);
  fout << "Исходный текст: " << endl;
  fout << endl;
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
  fout << endl;
  if (text != redacted_text) {
    fout << "Текст после редактирования: " << endl;
    fout << endl;
    for (int i = 0; i < redacted_text.size(); i++) {
      fout << redacted_text[i] << endl;
    }
    fout << endl;
  }
}

void PrintInitialData(const vector<string>& text, string path) { // Функция для вывода исходных данных в файл
  ofstream fout(path);
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
}

vector<string> FileInput(vector<string>& text) { // Функция для чтения данных из файла
  string pathInput;
  cout << "Введите путь к файлу: ";
  getline(cin, pathInput);
  ifstream fin(pathInput);
  while (true) {
    while (!fin || CheckPath(pathInput)) { // Проверка на существование файла по указанному пути
      fin.close();
      cerr << "Некорректное указание пути или имени файла." << endl;
      cout << "Введите путь к файлу: ";
      getline(cin, pathInput);
      fin.open(pathInput); // Открытие файла
      cout << endl;
    }
    break;
  }
  fin.seekg(0, ios::beg);
  string temp; // Переменная для временного хранения символов из файла
  while (!fin.eof()) {
    while (getline(fin, temp))
      text.push_back(temp);
  }
  fin.close();
  return text;
}

void SaveResult(const vector<string>& text, const vector<string>& redacted_text, string searchSymbol) { // Функция для сохранения результата в файл
  string pathOutput;
  int userChoice;
  cout << "Введите путь к файлу: ";
  getline(cin, pathOutput);
  ifstream fout(pathOutput);
  while (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // Проверка на корректный путь и имя файла
    fout.close();
    cerr << "Некорректное указание пути или имени файла." << endl;
    cout << "Введите путь к файлу: ";
    getline(cin, pathOutput);
    fout.open(pathOutput);
  }
  cout << endl;
  fout.close();
  while (fout) { // Если файл уже существует
    PrintAdditionalMenu(); // Вывод вспомогательного меню
    MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
    switch (userChoice) {
    case RewriteMenuItem: { // Вариант с перезаписью
      ofstream fout(pathOutput);
      PrintResult(text, redacted_text, searchSymbol, pathOutput);
      fout.close();
      break; }
    case CreateNewFileMenuItem: { // Вариант с созданием нового файла
      fout.close();
      SaveResult(text, redacted_text, searchSymbol);
      break; }
    case GoBackMenuItem: { // Вариант выйти обратно
      // ;
      break; }
    }
    break;
  }
  if (!fout) { // Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
    PrintResult(text, redacted_text, searchSymbol, pathOutput);
    fout.close();
  }
}

void SaveInitialData(const vector<string>& text) {  // Функция для записи исходных данных в файл
  string pathOutput;
  int userChoice;
  cout << "Введите путь к файлу: ";
  getline(cin, pathOutput);
  ifstream fout(pathOutput);
  while (CheckPath(pathOutput) || !CheckReadOnly(pathOutput)) { // Проверка на корректный путь и имя файла
    fout.close();
    cerr << "Некорректное указание пути или имени файла." << endl;
    cout << "Введите путь к файлу: ";
    getline(cin, pathOutput);
    fout.open(pathOutput);
  }
  cout << endl;
  fout.close();
  while (fout) { // Если файл уже существует
    PrintAdditionalMenu(); // Вывод вспомогательного меню
    MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
    switch (userChoice) {
    case RewriteMenuItem: { // Вариант с перезаписью
      ofstream fout(pathOutput);
      PrintInitialData(text, pathOutput);
      fout.close();
      break; }
    case CreateNewFileMenuItem: { // Вариант с созданием нового файла
      fout.close();
      SaveInitialData(text);
      break; }
    }
    break;
  }
  if (!fout) { // Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
    PrintInitialData(text, pathOutput);
    fout.close();
  }
}