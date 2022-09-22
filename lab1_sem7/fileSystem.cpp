#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

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

bool IsPathIncorrect(const string& path, const int context) { // Проверка на использование недопустимых знаков и/или зарезервированных имён
    error_code ec;
    if (context == SaveContext) { // Если проверка проходит в режиме сохранения
        if (ifstream(path)) {
            if (!is_regular_file(path, ec)) {
                return true;
            }
            return false;
        }
        ofstream fout(path, ofstream::_Noreplace);
        if (!is_regular_file(path, ec)) {
            return true;
        }
        if (!fout) {
            fout.close();
            return true;
        }
        fout.close();
        remove(path);
    }
    else { // Если проверка проходит в режиме открытия
        if (!ifstream(path)) {
            return true;
        }
        if (!is_regular_file(path, ec)) {
            return true;
        }
        ifstream fin(path);
        if (!fin) {
            fin.close();
            return true;
        }
        fin.close();
    }
    return false;
}

bool IsReadOnly(const string& path) { // Проверка файла на атрибут "только для чтения"
    WIN32_FIND_DATAA findData;
    LPCSTR name = path.c_str();
    FindFirstFileA(name, &findData);
    FindFirstFileA(name, &findData);
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
        return true;
    }
    else {
        return false;
    }
}

int CheckPath(const string& path, const int context) { // Проверка пути к файлу
    int userChoice;
    if (IsPathIncorrect(path, context) || IsReadOnly(path)) { // Проверка на корректный путь и имя файла
        if (IsPathIncorrect(path, context)) { // Если путь некорректен
            cerr << "Некорректное указание пути или имени файла." << endl;
            system("pause");
        }
        if (IsReadOnly(path)) { // Если файл "только для чтения"
            cerr << "Невозможно сохранить данные в файл, предназначенный только для чтения." << endl;
            system("pause");
        }
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
            return ErrorInPathInput;
            break;
        }
        case GoBackToMainMenuMenuItem: { // Вариант выйти в главное меню
            return GoBack;
            break; 
        }
        }
    }
    return NoError;
}

int CheckData(const vector<string>& text, const string& searchSymbol) { // Проверка данных, хранящихся в файле
    int userChoice;
    if (text.empty() || searchSymbol == "") { // Проверка исходных данных в файле
        cerr << "В файле недостаточно данных." << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: { // Вариант с вводом пути заново
            return ErrorInFileData;
            break;
        }
        case GoBackToMainMenuMenuItem: { // Вариант выйти в главное меню
            return GoBack;
            break; 
        }
        }
    }
    return NoError;
}

void PrintTextInFile(const vector<string>& text, const string& path) { // Запись данных в файл
    ofstream fout(path, ofstream::trunc);
    for (int i = 0; i < text.size(); i++) {
        if (i == text.size() - 1) {
            fout << text[i];
        }
        else {
            fout << text[i] << endl;
        }
    }
}

void ReadFromFile(vector<string>& text, string& searchSymbol, const string& path) { // Чтение данных из файла
    ifstream fin(path);
    fin.seekg(0, ios::beg);
    string temp;
    while (!fin.eof()) { // Чтение файла    
        temp = "";
        while (getline(fin, temp)) {
            text.push_back(temp);
        }
    }
    searchSymbol = text[0];
    text.erase(text.begin());
    fin.close();
}

int FileInput(vector<string>& text, string& searchSymbol) { // Чтение данных из файла и их проверка
    text.clear();
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "Введите путь к файлу: ";
        cin.ignore();
        getline(cin, path);
        errorCode = CheckPath(path, InputContext);
        switch (errorCode) {
        case NoError: {
            ReadFromFile(text, searchSymbol, path);
            errorCode = CheckData(text, searchSymbol);
            switch (errorCode) {
            case ErrorInFileData: {
                continue;
                break;
            }
            case GoBack: {
                return GoBack;
                break;
            }
            }
            break;
        }
        case ErrorInPathInput: {
            continue;
            break;
        }
        case GoBack: {
            return GoBack;
            break;
        }
        }
    } while (errorCode != NoError);
    return NoError;
}

int SaveFile(const vector<string>& text) { // Функция для создания файлов с результатами или исоходными данными
    int userChoice;
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "Введите путь к файлу: ";
        cin.ignore();
        getline(cin, path);
        errorCode = CheckPath(path, SaveContext);
        switch (errorCode) {
        case ErrorInPathInput: {
            continue;
            break;
        }
        case GoBack: {
            return GoBack;
            break;
        }
        }

        if (ifstream(path)) { // Если файл существует
            PrintAdditionalMenu(); // Вывод вспомогательного меню
            MenuInputCheck(&userChoice, RewriteMenuItem, GoBackMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // Вариант с перезаписью
                PrintTextInFile(text, path);
                break;
            }
            case CreateNewFileMenuItem: { // Вариант с созданием нового файла
                errorCode = ErrorInPathInput;
                continue;
                break;
            }
            case GoBackMenuItem: { // Выход в главное меню
                return GoBack;
                break;
            }
            }
        }
        else { // Если файл не существует
            //errorCode = CheckPath(path, SaveContext);
            PrintTextInFile(text, path);
        }
        cout << endl;
        cout << "Данные успешно сохранены." << endl;
        system("pause");
    } while (errorCode != NoError);
    return NoError;
}