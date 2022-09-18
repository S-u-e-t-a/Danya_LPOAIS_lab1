#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

bool IsPathIncorrect(string path, int context) { // Проверка на использование недопустимых знаков и/или зарезервированных имён
    // Разбиение пути на части
    size_t found = path.find_last_of("\\");
    size_t point = path.find_last_of(".");
    size_t base = point - found - 1;
    string basefilenameStr = path.substr(found + 1, base);
    const char* basefilenameChar = basefilenameStr.c_str();
    if (context == SaveContext) { // Если проверка проходит в режиме сохранения
        ofstream file(path, ios::app);
        if (!file) {
            file.close();
            return true;
        }
    }
    if (!_strcmpi(basefilenameChar, "con")) return true;
    if (!is_regular_file(path)) return true;
    return false;
}

bool IsReadOnly(string path) { // Проверка файла на атрибут "только для чтения"
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

int PathInput(string& path, int context) { // Ввод и проверка пути
    int userChoice;
    system("cls");
    cout << "Введите путь к файлу: ";
    cin >> path;
    //getline(cin, path);
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ifstream fout(path); // для сохранения
    while (IsPathIncorrect(path, context) || IsReadOnly(path)) { // Проверка на корректный путь и имя файла
        fout.close(); // для сохранения
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
            PathInput(path, context);
            break;
        }
        case GoBackToMainMenuMenuItem: { // Вариант выйти в главное меню
            Menu();
            return ErrorInPathInput; // ПОТЕСТИТЬ МБ НЕ НУЖЕН RETURN ЕСЛИ ВЫЗЫВАЮ МЕНЮ
            break; }
        }
    }
    return NoError;
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

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, string& path) { // Вспомогательная функция для записи результата в файл
    ofstream fout(path);
    fout << "Исходный текст: " << endl;
    fout << endl;
    for (int i = 0; i < text.size(); i++) {
        fout << text[i] << endl;
    }
    fout << endl;
    fout << "Символ поиска: " << searchSymbol << endl;
    fout << endl;
    fout << "Слова, имеющие данный символ: " << endl;
    fout << endl;
    for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
        fout << wordsWithSearchSymbol[i] << endl;
        fout << endl;
    }
}

void PrintInitialData(const vector<string>& text, string& path) { // Функция для записи исходных данных в файл
    ofstream fout(path);
    for (int i = 0; i < text.size(); i++) {
        fout << text[i] << endl;
    }
}

int FileInput(vector<string>& text, string& searchSymbol) { // Функция для чтения данных из файла
    text.clear();
    string path = "";
    int res = PathInput(path, InputContext);
    if (res == NoError) {
        ifstream fin(path);
        fin.seekg(0, ios::beg);
        string temp;
        int count = 0;
        while (!fin.eof()) { // Чтение файла
            temp = "";
            if (count == 0) {
                fin >> searchSymbol;
                count++;
            }
            while (getline(fin, temp))
                text.push_back(temp);
        }
        fin.close();
        return NoError;
    }
    else {
        return ErrorInFileFuncs;
    }
}

int SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, int context) { // Функция для создания файлов с результатами или исоходными данными
    int userChoice;
    string path;
    int res = PathInput(path, SaveContext);
    if (res == NoError) {
        remove(path);
        ifstream fout(path);
        //fout.close(); // хз зачем
        /*while*/ if (fout) { // Если файл уже существует
            PrintAdditionalMenu(); // Вывод вспомогательного меню
            MenuInputCheck(&userChoice, CreateNewFileMenuItem, GoBackMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // Вариант с перезаписью
                ofstream fout(path);
                switch (context) {
                case SaveResultContext: { // Сохранение результатов
                    PrintResult(text, wordsWithSearchSymbol, searchSymbol, path);
                    fout.close();
                    break; }
                case SaveInitialDataContext: { // Сохранение исходных данных
                    fout.close();
                    PrintInitialData(text, path);
                    break; }
                }
                break;
            }
            case CreateNewFileMenuItem: { // Вариант с созданием нового файла
                fout.close();
                SaveFile(text, wordsWithSearchSymbol, searchSymbol, context);
                break;
            }
            case GoBackMenuItem: { // Выход в главное меню
                Menu();
                break; }
            }
            //break;
            return NoError;
        }
        if (!fout) { // Если файла ещё не существует по данному пути
            switch (context) {
            case SaveResultContext: { // Сохранение результатов
                PrintResult(text, wordsWithSearchSymbol, searchSymbol, path);
                break; }
            case SaveInitialDataContext: { // Сохранение исходных данных
                PrintInitialData(text, path);
                break; }
            }
            fout.close();
            return NoError;
        }
    }
    else {
        return ErrorInFileFuncs;
    }
}