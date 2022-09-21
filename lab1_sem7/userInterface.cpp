#include "fileSystem.h"
#include "textFunctions.h"
#include "userInterface.h"

using namespace std;

void MenuInputCheck(int* userChoice, const int min, const int max) { // �������� ������� �����. ��������� ������� ������ �����
    if (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) { // ���� ���� ������������ �� �������� ������ ��� ��������� ��� �������� ������
        cin.clear();
        cout << endl;
        cerr << "������� ������������ ��������.";
        cout << endl;
        cout << "������� ��������: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        MenuInputCheck(userChoice, min, max);
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

void PrintWarning() {
    system("cls");
    cout << endl;
    cout << "��������! � ����� ������ ���� ��� ������� 2 ������." << endl;
    cout << "������ ������ �������� ������� ��������." << endl;
    cout << "����������� ������ �������� �������." << endl;
    cout << endl;
    system("pause");
}

void CreateText(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, vector<string>& createdText, int context) {
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

void ManualInput(vector<string>& text, string& searchSymbol) { // ������ ���� �������� ������
    string buffer;
    system("cls");
    cout << "������� �����." << endl;
    cout << "�� ��������� ����� ������� ������ ������." << endl;
    cout << endl;
    getline(cin, buffer);
    while (true) {
        getline(cin, buffer);
        if (buffer != "") { // �������� �����
            text.push_back(buffer);
        }
        else {
            if (text.size() == 0) {
                cout << "�� �� ����� �����." << endl;
                cout << "������� �����." << endl;
                cout << endl;
            }
            else {
                break;
            }
        }
    }
    cout << "������� ������ ��� ������: ";
    while (true) {
        getline(cin, searchSymbol);
        if (searchSymbol == "" || searchSymbol == "\t" || searchSymbol == "\n") { // �������� �����
            cout << "�� �� ����� ������ ��� ������." << endl;
            cout << "������� �����." << endl;
            cout << endl;
        }
        else {
            break;
        }
    }
}

void Menu() { // ������� ����
    int userChoice;
    int lastChoiceInMainMenu = NoMenuItem;
    vector<string> text;
    vector<string> wordsWithSearchSymbol;
    string searchSymbol;
    vector<string> createdText;
    PrintMenu();
    MenuInputCheck(&userChoice, ManualInputMenuItem, ExitMenuItem);
    cout << endl;
    switch (userChoice) {
    case ManualInputMenuItem: { // ������ ���� �������� ������
        lastChoiceInMainMenu = ManualInputMenuItem;
        ManualInput(text, searchSymbol);
        break;
    }
    case InputFromFileMenuItem: { // ���� �������� ������ �� �����
        lastChoiceInMainMenu = InputFromFileMenuItem;
        PrintWarning();
        FileInput(text, searchSymbol);
        PrintText(text, searchSymbol);
        break;
    }
    case ShowInfoMenuItem: { // ����� ���������� � ��������� � ������
        lastChoiceInMainMenu = ShowInfoMenuItem;
        Greeting();
        break;
    }
    case ExitMenuItem: { // ����� �� ���������
        lastChoiceInMainMenu = ExitMenuItem;
        cout << "��������� ���������." << endl;
        exit(0);
    }
    }
    if (lastChoiceInMainMenu == ManualInputMenuItem || lastChoiceInMainMenu == InputFromFileMenuItem) {
        SplitText(text, wordsWithSearchSymbol);
        FindSymbolInText(wordsWithSearchSymbol, searchSymbol);
        PrintResult(wordsWithSearchSymbol);
        PrintYesNoMenu("��������� ��������� � ����?");
        MenuInputCheck(&userChoice, Yes, No);
        switch (userChoice) {
        case Yes: {
            CreateText(text, wordsWithSearchSymbol, searchSymbol, createdText, SaveResultContext);
            SaveFile(createdText);
            break;
        }
        case No: { break; }
        }
        PrintYesNoMenu("��������� �������� ������ � ����?");
        MenuInputCheck(&userChoice, Yes, No);
        switch (userChoice) {
        case Yes: {
            CreateText(text, wordsWithSearchSymbol, searchSymbol, createdText, SaveResultContext);
            SaveFile(createdText);
            break;
        }
        case No: { break; }
        }
    }
}