#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

bool IsPathIncorrect(string path, int context) { // �������� �� ������������� ������������ ������ �/��� ����������������� ���
    // ��������� ���� �� �����
    size_t found = path.find_last_of("\\");
    size_t point = path.find_last_of(".");
    size_t base = point - found - 1;
    string basefilenameStr = path.substr(found + 1, base);
    const char* basefilenameChar = basefilenameStr.c_str();
    if (context == SaveContext) { // ���� �������� �������� � ������ ����������
        //ifstream file(path, ios::app); // �������� ���� �� ���� �����. ������� ���� � is_regular_file �� ����� ��� ��� ������
        //if (!file) { // ����� remove ����� � ����� ����� ������ � ����� ������, �� ���� ���� ���, �� ���Ш� ��� ������.
        //    //file.close();
        //    return true;
        //}

        if (!_strcmpi(basefilenameChar, "con")) return true;
        if (exists(path)) {
            if (!is_regular_file(path)) return true;
            return false;
        }
        else {
            return false;
        }

        //if (FILE* file = fopen(path.c_str(), "r")) {
        //    fclose(file);
        //    return false;
        //}
        //else {
        //    return true;
        //}
    }
    if (!_strcmpi(basefilenameChar, "con")) return true;
    if (!is_regular_file(path)) return true;
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

int PathInput(string& path, int context) { // ���� � �������� ����
    int userChoice;
    system("cls");
    cout << "������� ���� � �����: ";
    cin >> path;
    //getline(cin, path);
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ifstream fout(path); // ��� ����������
    if (IsPathIncorrect(path, context) || IsReadOnly(path)) { // �������� �� ���������� ���� � ��� �����
        fout.close(); // ��� ����������
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
            PathInput(path, context);
            break;
        }
        case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
            //Menu();
            return ErrorInPathInput; // ��������� �� �� ����� RETURN ���� ������� ����
            break; }
        }
    }
    return NoError;
}

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

void PrintResultInFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, string& path) { // ��������������� ������� ��� ������ ���������� � ����
    ofstream fout(path);
    fout << "�������� �����: " << endl;
    fout << endl;
    for (int i = 0; i < text.size(); i++) {
        fout << text[i] << endl;
    }
    fout << endl;
    fout << "������ ������: " << searchSymbol << endl;
    fout << endl;
    fout << "�����, ������� ������ ������: " << endl;
    fout << endl;
    for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
        fout << wordsWithSearchSymbol[i] << endl;
        fout << endl;
    }
}

void PrintInitialDataInFile(const vector<string>& text, const string& searchSymbol, string& path) { // ������� ��� ������ �������� ������ � ����
    ofstream fout(path);
    fout << searchSymbol << endl;
    for (int i = 0; i < text.size(); i++) {
        if (i == text.size() - 1) {
            fout << text[i];
        }
        else {
            fout << text[i] << endl;
        }
    }
}

void FileInput(vector<string>& text, string& searchSymbol) { // ������� ��� ������ ������ �� �����
    text.clear();
    string path = "";
    int errorCode = PathInput(path, InputContext);
    if (errorCode == NoError) {
        ifstream fin(path);
        fin.seekg(0, ios::beg);
        string temp;
        int count = 0;
        while (!fin.eof()) { // ������ �����
            temp = "";
            if (count == 0) {
                fin >> searchSymbol;
                count++;
            }
            while (getline(fin, temp))
                text.push_back(temp);
        }
        fin.close();
        if (text.empty() || searchSymbol == "") { // �������� �������� ������ � �����
            cout << "� ����� ������������ ������." << endl;
            system("pause");
            int userChoice;
            PrintErrorMenu();
            MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
            switch (userChoice) {
            case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
                FileInput(text, searchSymbol);
                break;
            }
            case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
                Menu();
                break; }
            }

        }
        //return NoError;
    }
    else {
        //return ErrorInFileFuncs;
        Menu();
    }
}

int SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, int context) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
    int userChoice;
    string path;
    int errorCode = PathInput(path, SaveContext);
    if (errorCode == NoError) {
        //remove(path);
        fstream fout(path);
        //fout.close(); // �� �����
        /*while*/ if (exists(path)) { // ���� ���� ��� ����������
            PrintAdditionalMenu(); // ����� ���������������� ����
            MenuInputCheck(&userChoice, RewriteMenuItem, GoBackMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // ������� � �����������
                //ofstream fout(path);
                switch (context) {
                case SaveResultContext: { // ���������� �����������
                    PrintResultInFile(text, wordsWithSearchSymbol, searchSymbol, path);
                    break; }
                case SaveInitialDataContext: { // ���������� �������� ������
                    PrintInitialDataInFile(text, searchSymbol, path);
                    break; }
                }
                break;
            }
            case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
                SaveFile(text, wordsWithSearchSymbol, searchSymbol, context);
                break;
            }
            case GoBackMenuItem: { // ����� � ������� ����
                Menu();
                break; }
            }
            //break;
        }
        if (!exists(path)) { // ���� ����� ��� �� ���������� �� ������� ����
            switch (context) {
            case SaveResultContext: { // ���������� �����������
                PrintResultInFile(text, wordsWithSearchSymbol, searchSymbol, path);
                break; }
            case SaveInitialDataContext: { // ���������� �������� ������
                PrintInitialDataInFile(text, searchSymbol, path);
                break; }
            }
        }
        fout.close();
        cout << "������ ������� ���������." << endl;
        system("pause");
        return NoError;
    }
    else {
        return ErrorInFileFuncs;
    }
}