#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

void PrintAdditionalMenu() { // ��������������� ����, ���� � ���� ���������� ����� ��� ��������� ��� ������������ ����
    system("cls");
    cout << "������ ���� ��� ����������." << endl;
    cout << endl;
    cout << "\t��� �� ������ �������?" << endl;
    cout << "1. ������������ ����." << endl;
    cout << "2. ������� ����� ����." << endl;
    cout << "3. ��������� � ������� ����." << endl;
    cout << endl;
    cout << "�������� ����� ����: ";
}

bool IsPathIncorrect(const string& path, const int context) { // �������� �� ������������� ������������ ������ �/��� ����������������� ���
    error_code ec;
    if (context == SaveContext) { // ���� �������� �������� � ������ ����������
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
    else { // ���� �������� �������� � ������ ��������
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

bool IsReadOnly(const string& path) { // �������� ����� �� ������� "������ ��� ������"
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

int CheckPath(const string& path, const int context) { // �������� ���� � �����
    int userChoice;
    if (IsPathIncorrect(path, context) || IsReadOnly(path)) { // �������� �� ���������� ���� � ��� �����
        if (IsPathIncorrect(path, context)) { // ���� ���� �����������
            cerr << "������������ �������� ���� ��� ����� �����." << endl;
            system("pause");
        }
        if (IsReadOnly(path)) { // ���� ���� "������ ��� ������"
            cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
            system("pause");
        }
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
            return ErrorInPathInput;
            break;
        }
        case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
            return GoBack;
            break; 
        }
        }
    }
    return NoError;
}

int CheckData(const vector<string>& text, const string& searchSymbol) { // �������� ������, ���������� � �����
    int userChoice;
    if (text.empty() || searchSymbol == "") { // �������� �������� ������ � �����
        cerr << "� ����� ������������ ������." << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
            return ErrorInFileData;
            break;
        }
        case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
            return GoBack;
            break; 
        }
        }
    }
    return NoError;
}

void PrintTextInFile(const vector<string>& text, const string& path) { // ������ ������ � ����
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

void ReadFromFile(vector<string>& text, string& searchSymbol, const string& path) { // ������ ������ �� �����
    ifstream fin(path);
    fin.seekg(0, ios::beg);
    string temp;
    while (!fin.eof()) { // ������ �����    
        temp = "";
        while (getline(fin, temp)) {
            text.push_back(temp);
        }
    }
    searchSymbol = text[0];
    text.erase(text.begin());
    fin.close();
}

int FileInput(vector<string>& text, string& searchSymbol) { // ������ ������ �� ����� � �� ��������
    text.clear();
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "������� ���� � �����: ";
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

int SaveFile(const vector<string>& text) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
    int userChoice;
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "������� ���� � �����: ";
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

        if (ifstream(path)) { // ���� ���� ����������
            PrintAdditionalMenu(); // ����� ���������������� ����
            MenuInputCheck(&userChoice, RewriteMenuItem, GoBackMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // ������� � �����������
                PrintTextInFile(text, path);
                break;
            }
            case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
                errorCode = ErrorInPathInput;
                continue;
                break;
            }
            case GoBackMenuItem: { // ����� � ������� ����
                return GoBack;
                break;
            }
            }
        }
        else { // ���� ���� �� ����������
            //errorCode = CheckPath(path, SaveContext);
            PrintTextInFile(text, path);
        }
        cout << endl;
        cout << "������ ������� ���������." << endl;
        system("pause");
    } while (errorCode != NoError);
    return NoError;
}