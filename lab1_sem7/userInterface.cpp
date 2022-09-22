#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"

using namespace std;

void MenuInputCheck(int* userChoice, const int min, const int max) { // Проверка ручного ввода. Позволяет вводить только числа
    while (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) { // Если ввод пользователя не является цифрой или находится вне заданных границ
        cin.clear();
        cout << endl;
        cerr << "Введено неправильное значение.";
        cout << endl;
        cout << "Введите значение: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << "2. Ввести текст из файла." << endl;
    cout << "3. Вывести информацию о программе и авторе." << endl;
    cout << "4. Выйти из программы." << endl;
    cout << endl;
    cout << "Выберите пункт меню: ";
}

void PrintYesNoMenu(const string& msg) { // Вывод вспомогательного меню с выбором «Да» и «Нет»
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

void PrintWarning() { // Вывод в консоль сообщения о данных, которые должны находиться в файле с исходными данными
    system("cls");
    cout << "Внимание! В файле должно быть как минимум 2 строки." << endl;
    cout << "Первая строка является искомым символом." << endl;
    cout << "Последующие строки являются текстом." << endl;
    cout << endl;
    system("pause");
}

void CreateText(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, vector<string>& createdText, int context) { // Создание текста для сохранения в файл
    createdText.clear();
    switch (context) {
    case SaveResultContext: {
        createdText.push_back("Исходный текст:");
        createdText.push_back("");
        for (int i = 0; i < text.size(); i++) {
            createdText.push_back(text[i]);
        }
        createdText.push_back("");
        createdText.push_back("Символ поиска: " + searchSymbol);
        createdText.push_back("");
        createdText.push_back("Результат поиска:");
        createdText.push_back("");
        if (!wordsWithSearchSymbol.empty()) {
            for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
                createdText.push_back(wordsWithSearchSymbol[i]);
            }
        }
        else {
            createdText.push_back("В тексте не найден искомый символ.");
        }
        break;
    }
    case SaveInitialDataContext: {
        createdText.push_back(searchSymbol);
        for (int i = 0; i < text.size(); i++) {
            createdText.push_back(text[i]);
        }
        break;
    }
    }
}

int TextInput(vector<string>& text) { // Ручной ввод текста и его проверка
    int userChoice;
    string temp;
    while (true) {
        cin.ignore();
        getline(cin, temp);
        if (temp != "") {
            text.push_back(temp);
        }
        else {
            if (text.size() == 0) {
                cerr << "Вы не ввели текст." << endl;
                system("pause");
                PrintErrorMenu();
                MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
                switch (userChoice) {
                case EnterDataAgainMenuItem: {
                    return ErrorInTextInput;
                    break;
                }
                case GoBackToMainMenuMenuItem: {
                    return GoBack;
                    break;
                }
                }
            }
            else {
                return NoError;
            }
        }
    }
}

int SymbolInput(string& searchSymbol) { // Ручной ввод искомого символа и его проверка
    int userChoice;
    cin.ignore();
    getline(cin, searchSymbol);
    if (searchSymbol == "" || searchSymbol == "\t" || searchSymbol == "\n") {
        cerr << "Вы не ввели символ для поиска." << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: {
            return ErrorInSymbolInput;
            break;
        }
        case GoBackToMainMenuMenuItem: {
            return GoBack;
            break;
        }
        }
    }
    return NoError;
}

int ManualInput(vector<string>& text, string& searchSymbol) { // Ручной ввод исходных данных
    int errorCode = NoError;
    string temp;
    do {
        system("cls");
        cout << "Введите текст." << endl;
        cout << "По окончании ввода введите пустую строку." << endl;
        cout << endl;
        errorCode = TextInput(text);
        switch (errorCode) {
        case ErrorInTextInput: {
            continue;
            break;
        }
        case GoBack: {
            return GoBack;
            break;
        }
        }
        cout << "Введите символ для поиска: ";
        errorCode = SymbolInput(searchSymbol);
        cout << endl;
        switch (errorCode) {
        case ErrorInSymbolInput: {
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

void Menu() { // Главное меню
    int userChoice;
    int errorCode = GoBack;
    vector<string> text;
    vector<string> wordsWithSearchSymbol;
    string searchSymbol;
    vector<string> createdText;
    do {
        PrintMenu();
        MenuInputCheck(&userChoice, ManualInputMenuItem, ExitMenuItem);
        cout << endl;
        switch (userChoice) {
        case ManualInputMenuItem: { // Ручной ввод исходных данных
            errorCode = ManualInput(text, searchSymbol);
            if (errorCode == GoBack) {
                continue;
            }
            break;
        }
        case InputFromFileMenuItem: { // Ввод исходных данных из файла
            PrintWarning();
            errorCode = FileInput(text, searchSymbol);
            if (errorCode == GoBack) {
                continue;
            }
            PrintText(text, searchSymbol);
            break;
        }
        case ShowInfoMenuItem: { // Вывод информации о программе и авторе
            Greeting();
            break;
        }
        case ExitMenuItem: { // Выход из программы
            cout << "Программа завершена." << endl;
            exit(0);
        }
        }
        if (userChoice == ManualInputMenuItem || userChoice == InputFromFileMenuItem) {
            SplitText(text, wordsWithSearchSymbol);
            FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
            PrintResult(wordsWithSearchSymbol);
            PrintYesNoMenu("Сохранить результат в файл?");
            MenuInputCheck(&userChoice, Yes, No);
            switch (userChoice) {
            case Yes: {
                CreateText(text, wordsWithSearchSymbol, searchSymbol, createdText, SaveResultContext);
                errorCode = SaveFile(createdText);
                if (errorCode == GoBack) {
                    continue;
                }
                break;
            }
            case No: { break; }
            }
            system("cls");
            createdText.clear();
            PrintYesNoMenu("Сохранить исходные данные в файл?");
            MenuInputCheck(&userChoice, Yes, No);
            switch (userChoice) {
            case Yes: {
                CreateText(text, wordsWithSearchSymbol, searchSymbol, createdText, SaveInitialDataContext);
                errorCode = SaveFile(createdText);

                break;
            }
            case No: { break; }
            }
        }
    } while (errorCode != NoError);
}