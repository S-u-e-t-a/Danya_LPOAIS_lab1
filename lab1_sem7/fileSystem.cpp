#include "fileSystem.h"
#include "userInterface.h"
#include "exceptions.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

bool IsPathGood(string path) { // Проверка пути
  size_t found = path.find_last_of("\\");
  size_t point = path.find_last_of(".");
  size_t base = point - found - 1;
  string baseFilenameStr = path.substr(found + 1, base);
  const char* basefilenameChar = baseFilenameStr.c_str();
  ofstream file(path, ios::app);
  //if (!_strcmpi(basefilenameChar, "con")) {
  //  file.close(); // мб не надо
  //  throw WrongPathInput("Некорректное указание пути или имени файла.", filename, context);
  //}
  //if (!std::filesystem::is_regular_file(filename)) {   НАЙТИ ЗАМЕНУ ДЛЯ 14 СТАНДАРТА
  //  file.close(); // мб не надо
  //  throw WrongPathInput("Некорректное указание пути или имени файла.", filename);
  //}
  //file.close();
  if (_strcmpi(basefilenameChar, "con")) return false;
  if (is_regular_file(path)) return false;
  file.close();
  return true;
}

bool IsReadOnly(string path) { // Проверка файла на атрибут "только для чтения"
  ofstream file(path);
  WIN32_FIND_DATAA findData;
  LPCSTR name = path.c_str();
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    //throw FileIsReadOnly("Невозможно сохранить данные в файл, предназначенный только для чтения.", context);
    return true;
  }
  return false;
}

void PathInput(string& path) {
  int userChoice;
  system("cls");
  cout << "Введите путь к файлу: ";
  //cin.get();
  getline(cin, path);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  while (IsPathGood(path) || IsReadOnly(path)) { // Проверка на корректный путь и имя файла
    if (IsPathGood(path)) {
      cerr << "Некорректное указание пути или имени файла." << endl;
    }
    if (IsReadOnly(path)) {
      cerr << "Невозможно сохранить данные в файл, предназначенный только для чтения." << endl;
    }
    PrintErrorMenu();
    MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
    switch (userChoice) {
    case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
      PathInput(path);
      //switch (context) { // Вызов метода, в котором произошлfа ошибка
      //case SaveResultContext: {
      //  SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      //  break; }
      //case SaveInitialDataContext: {
      //  SaveFile(text, wordsWithSearchSymbol, searchSymbol, ex.GetContext());
      //  break; }
      //case InputContext: {
      //  FileInput(text, searchSymbol);
      //  PrintText(text, searchSymbol);
      //  SplitText(text, wordsWithSearchSymbol);
      //  FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
      //  PrintResult(wordsWithSearchSymbol);
      //  SaveData(text, wordsWithSearchSymbol, searchSymbol);
      //  break; }
      //}
      break;
    }
    case GoBackToMainMenuMenuItem: { // Вариант выйти в главное меню
      PrintMenu();
      break; }
    }
    /*cout << "Введите путь к файлу: ";
    getline(cin, path);*/
  }
}

void PrintAdditionalMenu() { // Вспомогательное меню, если в ходе сохранения файла был обнаружен уже существующий файл
  system("cls");
  cout << "Данный файл уже существует." << endl;
  cout << endl;
  cout << "\tЧто вы хотите сделать?" << endl;
  cout << "1. Перезаписать файл." << endl;
  cout << "2. Создать новый файл." << endl;
  cout << "3. Вернуться в главное меню." << endl;
  cout << endl;
  cout << "Выберите пункт меню: ";
}

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, string& path) { // Вспомогательная функция для записи данных в файл
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

void PrintInitialData(const vector<string>& text, string& path) { // Функция для записи исходных данных в файл
  ofstream fout(path);
  for (int i = 0; i < text.size(); i++) {
    fout << text[i] << endl;
  }
}

void FileInput(vector<string>& text, string& searchSymbol) { // Функция для чтения данных из файла
  text.clear();
  string pathInput = "";
  PathInput(pathInput);
  //system("cls");
  //cout << "Введите путь к файлу: ";
  //getline(cin, pathInput);
  //CheckPath(pathInput);

  ifstream fin(pathInput);
  fin.seekg(0, ios::beg);
  string temp; // Переменная для временного хранения символов из файла
  int count = 0;
  while (!fin.eof()) {  // При вводе любой строки зацикливается + создаётся файл с названием строки
    if (count == 0) {
      fin >> searchSymbol;
      count++;
    }
    while (getline(fin, temp))
      text.push_back(temp);
  }
  fin.close();
}

void SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, int saveContext) { // Функция для создания файлов с результатами или исоходными данными
  //system("cls");
  //cout << "Введите путь к файлу: ";
  //getline(cin, pathInput);
  //CheckPath(pathInput);
  //CheckReadOnly(pathOutput);
  int userChoice;
  string pathOutput;
  PathInput(pathOutput);
  ifstream fout(pathOutput);
  //cout << endl;
  fout.close();
  /*while*/ if (fout) { // Если файл уже существует
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
      SaveFile(text, wordsWithSearchSymbol, searchSymbol, saveContext);
      break;
    }
    case GoBackMenuItem: { // Вариант выйти в главное меню
      PrintMenu();
      break; }
    }
    //break;
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