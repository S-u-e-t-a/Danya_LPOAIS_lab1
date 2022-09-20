#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"
#include "tests.h"

using namespace std;

void MenuInputCheck(int* userChoice, const int min, const int max) { // Проверка ручного ввода. Позволяет вводить только числа
    if (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) { // Если ввод пользователя не является цифрой или находится вне заданных границ
        cin.clear();
        cout << endl;
        cerr << "Введено неправильное значение.";
        cout << endl;
        cout << "Введите значение: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        MenuInputCheck(userChoice, min, max);
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

void PrintMenu() { // Вывод меню
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

void PrintYesNoMenu(const string msg) { // Вывод вспомогательного меню с выбором «Да» и «Нет»
    cout << msg << endl;
    cout << "1 - Да | 2 - Нет" << endl;
    cout << endl;
    cout << "Выбор: ";
}

void PrintErrorMenu() { // Вывод вспомогательного меню при возникновении ошибки
    system("cls");
    cout << "\tЧто вы хотите сделать?" << endl;
    cout << "1. Ввести данные заново." << endl;
    cout << "2. Вернуться в главное меню." << endl;
    cout << endl;
    cout << "Выберите пункт меню: ";
}

void PrintText(const vector<string>& text, const string& searchSymbol) { // Вывод исходных данных
    system("cls");
    cout << "Ваш текст:" << endl;
    cout << endl;
    for (int i = 0; i < text.size(); i++) {
        cout << text[i] << endl;
    }
    cout << endl;
    cout << "Символ поиска: " << searchSymbol;
    cout << endl;
}

void PrintResult(const vector<string>& wordsWithSearchSymbol) { // Вывод в консоль результата работы программы
    cout << "Результат поиска:" << endl;
    cout << endl;
    if (!wordsWithSearchSymbol.empty()) {
        for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
            cout << wordsWithSearchSymbol[i] << endl;
        }
    }
    else {
        cout << "В тексте не найден искомый символ." << endl;
    }
    cout << endl;
}

void ManualInput(vector<string>& text, string& searchSymbol) { // Ручной ввод исходных данных
    string buffer;
    system("cls");
    cout << "Введите текст." << endl;
    cout << "По окончании ввода введите пустую строку." << endl;
    cout << endl;
    getline(cin, buffer);
    while (true) {
        getline(cin, buffer);
        if (buffer != "") { // Проверка ввода
            text.push_back(buffer);
        }
        else {
            if (text.size() == 0) {
                cout << "Вы не ввели текст." << endl;
                cout << "Введите текст." << endl;
                cout << endl;
            }
            else {
                break;
            }
        }
    }
    cout << "Введите символ для поиска: ";
    cin >> searchSymbol;                                                        // ПРОВЕРЯТЬ?
}

void SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol) { // Сохранение данных
    int userChoice;
    int errorCode;
    PrintYesNoMenu("Сохранить результат в файл?");
    MenuInputCheck(&userChoice, Yes, No);
    switch (userChoice) {
    case Yes: {
        errorCode = SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveResultContext); // Вызов функции создания файла в режиме сохранения результата
        if (errorCode == ErrorInFileFuncs) { // Если в ходе работы функции сохранения произошла ошибка, то функция прерывается // и возвращает код ошибки
            system("pause");
            Menu();
        }
        break;
    }
    case No: { break; }
    }
    system("cls");
    PrintYesNoMenu("Сохранить исходные данные в файл?");
    MenuInputCheck(&userChoice, Yes, No);
    switch (userChoice) {
    case Yes: {
        errorCode = SaveFile(text, wordsWithSearchSymbol, searchSymbol, SaveInitialDataContext); // Вызов функции создания файла в режиме сохранения исходных данных
        if (errorCode == ErrorInFileFuncs) { // Если в ходе работы функции сохранения произошла ошибка, то функция прерывается // и возвращает код ошибки
            system("pause");
            Menu();
        }
        break;
    }
    case No: { break; }
    }
}

void Menu() { // Главное меню
    int userChoice;
    vector<string> text;
    vector<string> wordsWithSearchSymbol;
    string searchSymbol;
    PrintMenu();
    MenuInputCheck(&userChoice, ManualInputMenuItem, ExitMenuItem);
    cout << endl;
    switch (userChoice) {
    case ManualInputMenuItem: { // Ручной ввод исходных данных
        ManualInput(text, searchSymbol);
        SplitText(text, wordsWithSearchSymbol);
        FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
        PrintResult(wordsWithSearchSymbol);
        SaveData(text, wordsWithSearchSymbol, searchSymbol);
        break;
    }
    case InputFromFileMenuItem: { // Ввод исходных данных из файла
        FileInput(text, searchSymbol);
        PrintText(text, searchSymbol);
        SplitText(text, wordsWithSearchSymbol);
        FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
        PrintResult(wordsWithSearchSymbol);
        SaveData(text, wordsWithSearchSymbol, searchSymbol);
        break;
    }
    case ShowInfoMenuItem: { // Вывод информации о программе и авторе
        Greeting();
        break;
    }
    case UnitTestMenuItem: { // Вызов модульного тестирования
        RunModuleTests();
        break;
    }
    case ExitMenuItem: { // Выход из программы
        cout << "Программа завершена." << endl;
        exit(0);
    }
    }
}

