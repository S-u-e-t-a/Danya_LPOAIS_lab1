#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"

using namespace std;

void MenuInputCheck(int* userChoice, const int min, const int max) { // �������� ������� �����. ��������� ������� ������ �����
    while (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) { // ���� ���� ������������ �� �������� ������ ��� ��������� ��� �������� ������
        cin.clear();
        cout << endl;
        cerr << "������� ������������ ��������.";
        cout << endl;
        cout << "������� ��������: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Greeting() { // ����������
    system("cls");
    cout << "������������ ������ �1" << endl;
    cout << "������� 5" << endl;
    cout << endl;
    cout << "������ ��������� ���������� ����� ���� ���� � ������, ���������� �������� ������." << endl;
    cout << "���� ������ ����� ����������� ������� ��� ������ ���� ������� .txt." << endl;
    cout << "� ��������� ����������� ������� ���������� �������� ������ �" << endl;
    cout << "����������� ������ ��������� � ���� �������.txt." << endl;
    cout << endl;
    cout << "�����: ������� ������" << endl;
    cout << "������: 494" << endl;
    cout << endl;
    system("pause");
}

void PrintMenu() { // ����� ����
    system("cls");
    cout << "\t������� ����" << endl;
    cout << "�������� �������:" << endl;
    cout << "1. ������ ����� �������." << endl;
    cout << "2. ������ ����� �� �����." << endl;
    cout << "3. ������� ���������� � ��������� � ������." << endl;
    cout << "4. ����� �� ���������." << endl;
    cout << endl;
    cout << "�������� ����� ����: ";
}

void PrintYesNoMenu(const string& msg) { // ����� ���������������� ���� � ������� ��� � ����
    cout << msg << endl;
    cout << "1 - �� | 2 - ���" << endl;
    cout << endl;
    cout << "�����: ";
}

void PrintErrorMenu() { // ����� ���������������� ���� ��� ������������� ������
    system("cls");
    cout << "\t��� �� ������ �������?" << endl;
    cout << "1. ������ ������ ������." << endl;
    cout << "2. ��������� � ������� ����." << endl;
    cout << endl;
    cout << "�������� ����� ����: ";
}

void PrintText(const vector<string>& text, const string& searchSymbol) { // ����� �������� ������
    system("cls");
    cout << "��� �����:" << endl;
    cout << endl;
    for (int i = 0; i < text.size(); i++) {
        cout << text[i] << endl;
    }
    cout << endl;
    cout << "������ ������: " << searchSymbol;
    cout << endl;
}

void PrintResult(const vector<string>& wordsWithSearchSymbol) { // ����� � ������� ���������� ������ ���������
    cout << "��������� ������:" << endl;
    cout << endl;
    if (!wordsWithSearchSymbol.empty()) {
        for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
            cout << wordsWithSearchSymbol[i] << endl;
        }
    }
    else {
        cout << "� ������ �� ������ ������� ������." << endl;
    }
    cout << endl;
}

void PrintWarning() { // ����� � ������� ��������� � ������, ������� ������ ���������� � ����� � ��������� �������
    system("cls");
    cout << "��������! � ����� ������ ���� ��� ������� 2 ������." << endl;
    cout << "������ ������ �������� ������� ��������." << endl;
    cout << "����������� ������ �������� �������." << endl;
    cout << endl;
    system("pause");
}

void CreateText(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, vector<string>& createdText, int context) { // �������� ������ ��� ���������� � ����
    createdText.clear();
    switch (context) {
    case SaveResultContext: {
        createdText.push_back("�������� �����:");
        createdText.push_back("");
        for (int i = 0; i < text.size(); i++) {
            createdText.push_back(text[i]);
        }
        createdText.push_back("");
        createdText.push_back("������ ������: " + searchSymbol);
        createdText.push_back("");
        createdText.push_back("��������� ������:");
        createdText.push_back("");
        if (!wordsWithSearchSymbol.empty()) {
            for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
                createdText.push_back(wordsWithSearchSymbol[i]);
            }
        }
        else {
            createdText.push_back("� ������ �� ������ ������� ������.");
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

int TextInput(vector<string>& text) { // ������ ���� ������ � ��� ��������
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
                cerr << "�� �� ����� �����." << endl;
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

int SymbolInput(string& searchSymbol) { // ������ ���� �������� ������� � ��� ��������
    int userChoice;
    cin.ignore();
    getline(cin, searchSymbol);
    if (searchSymbol == "" || searchSymbol == "\t" || searchSymbol == "\n") {
        cerr << "�� �� ����� ������ ��� ������." << endl;
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

int ManualInput(vector<string>& text, string& searchSymbol) { // ������ ���� �������� ������
    int errorCode = NoError;
    string temp;
    do {
        system("cls");
        cout << "������� �����." << endl;
        cout << "�� ��������� ����� ������� ������ ������." << endl;
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
        cout << "������� ������ ��� ������: ";
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

void Menu() { // ������� ����
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
        case ManualInputMenuItem: { // ������ ���� �������� ������
            errorCode = ManualInput(text, searchSymbol);
            if (errorCode == GoBack) {
                continue;
            }
            break;
        }
        case InputFromFileMenuItem: { // ���� �������� ������ �� �����
            PrintWarning();
            errorCode = FileInput(text, searchSymbol);
            if (errorCode == GoBack) {
                continue;
            }
            PrintText(text, searchSymbol);
            break;
        }
        case ShowInfoMenuItem: { // ����� ���������� � ��������� � ������
            Greeting();
            break;
        }
        case ExitMenuItem: { // ����� �� ���������
            cout << "��������� ���������." << endl;
            exit(0);
        }
        }
        if (userChoice == ManualInputMenuItem || userChoice == InputFromFileMenuItem) {
            SplitText(text, wordsWithSearchSymbol);
            FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
            PrintResult(wordsWithSearchSymbol);
            PrintYesNoMenu("��������� ��������� � ����?");
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
            PrintYesNoMenu("��������� �������� ������ � ����?");
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