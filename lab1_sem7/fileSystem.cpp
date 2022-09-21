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

bool IsPathIncorrect(string path, int context) { // �������� �� ������������� ������������ ������ �/��� ����������������� ���
    error_code ec;
    if (context == SaveContext) { // ���� �������� �������� � ������ ����������
        ofstream fout(path, ofstream::app, ofstream::_Noreplace);
        if (!is_regular_file(path, ec)) {
            return true;
        }
        if (!fout) {
            fout.close();
            return true;
        }
        fout.close();
    }
    else { // �������� � ������ ��������
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

bool IsReadOnly(string path) { // �������� ����� �� ������� "������ ��� ������"
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

int CheckPath(string& path, int context) { // ���� � �������� ����
    int userChoice;
    while (IsPathIncorrect(path, context) || IsReadOnly(path)) { // �������� �� ���������� ���� � ��� �����
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
            continue;
            break;
        }
        case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
            return ErrorInPathInput;
            break; }
        }
    }
    return NoError;
}

void PrintTextInFile(const vector<string>& text, string& path) { // 
    ofstream fout(path, ofstream::trunc, ofstream::app);
    for (int i = 0; i < text.size(); i++) {
        if (i == text.size() - 1) {
            fout << text[i];
        }
        fout << text[i] << endl;
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

void FileInput(vector<string>& text, string& searchSymbol) { // ������ ������ �� ����� � �� ��������
    text.clear();
    int userChoice;
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "������� ���� � �����: ";
        cin >> path;
        errorCode = CheckPath(path, InputContext);
        if (errorCode == NoError) {
            ReadFromFile(text, searchSymbol, path);
            if (text.empty() || searchSymbol == "") { // �������� �������� ������ � �����
                cout << "� ����� ������������ ������." << endl;
                system("pause");
                PrintErrorMenu();
                MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
                switch (userChoice) {
                case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
                    continue;
                    break;
                }
                case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
                    Menu();
                    break; }
                }
            }
        }
    } while (errorCode != NoError);
}

void SaveFile(const vector<string>& text) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
    int userChoice;
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "������� ���� � �����: ";
        cin >> path;
        if (ifstream(path)) { // ���� ���� ����������
            PrintAdditionalMenu(); // ����� ���������������� ����
            MenuInputCheck(&userChoice, RewriteMenuItem, GoBackMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // ������� � �����������
                PrintTextInFile(text, path);
            }
            case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
                continue;
                break;
            }
            case GoBackMenuItem: { // ����� � ������� ����
                Menu();
                break;
            }
            }
        }
        else { // ���� ���� �� ����������
            errorCode = CheckPath(path, SaveContext);
            PrintTextInFile(text, path);
        }
        //fout.close();
        cout << "������ ������� ���������." << endl;
        system("pause");
    } while (errorCode != NoError);
}