#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

//bool IsPathIncorrect(string path, int context) { // �������� �� ������������� ������������ ������ �/��� ����������������� ���
//    // ��������� ���� �� �����
//    size_t found = path.find_last_of("\\");
//    size_t point = path.find_last_of(".");
//    size_t base = point - found - 1;
//    string basefilenameStr = path.substr(found + 1, base);
//    const char* basefilenameChar = basefilenameStr.c_str();
//    if (context == SaveContext) { // ���� �������� �������� � ������ ����������
//        if (!_strcmpi(basefilenameChar, "con")) return true;                        //  TODO: �������� �� ����������������� �����
//        if (exists(path)) {
//            if (!is_regular_file(path)) return true;
//            return false;
//        }
//        else {
//            return false;
//        }
//    }
//    if (!_strcmpi(basefilenameChar, "con")) return true;
//    if (!is_regular_file(path)) return true;
//    return false;
//}

bool IsPathIncorrect(string path, int context) { // �������� �� ������������� ������������ ������ �/��� ����������������� ���
    error_code ec;
    if (context == SaveContext) { // ���� �������� �������� � ������ ����������
        ofstream fout(path, ofstream::app);
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

int PathInput(string& path, int context) { // ���� � �������� ����
    int userChoice;
    //system("cls");
    //cout << "������� ���� � �����: ";
    //cin >> path;
    //getline(cin, path);
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            //int errorCode = PathInput(path, context);                          //  TODO: ������ ��������  TODO: ERRORCODE �� ������������ (������?)
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
    ofstream fout(path, ofstream::trunc);
    fout << "�������� �����: " << endl;
    fout << endl;
    for (int i = 0; i < text.size(); i++) {
        fout << text[i] << endl;
    }
    fout << endl;
    fout << "������ ������: " << searchSymbol << endl;
    fout << endl;
    fout << "��������� ������:" << endl;
    fout << endl;
    if (!wordsWithSearchSymbol.empty()) {
        for (int i = 0; i < wordsWithSearchSymbol.size(); i++) {
            fout << wordsWithSearchSymbol[i] << endl;
        }
    }
    else {
        fout << "� ������ �� ������ ������� ������." << endl;
    }
}

void PrintInitialDataInFile(const vector<string>& text, const string& searchSymbol, string& path) { // ������� ��� ������ �������� ������ � ����
    ofstream fout(path, ofstream::trunc);
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
    if (errorCode == NoError) { // TODO: ������� ���� DO WHILE?
        ifstream fin(path);
        fin.seekg(0, ios::beg);

        //  TODO: �������� �����������

        string temp;
        int count = 0;
        while (!fin.eof()) { // ������ �����   //  TODO: ��������� �������
            temp = "";
            if (count == 0) {
                fin >> searchSymbol;            // TODO: ������ FIN ������� READ
                count++;
            }
            while (getline(fin, temp)) {
                text.push_back(temp);
            }
            text.erase(text.begin());
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
                FileInput(text, searchSymbol); //  TODO: ������ ��������
                break;
            }
            case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
                Menu();
                break; }
            }

        }
    }
    else {
        Menu();
    }
}

// TODO: ������� ������� ������� ��������� ������ �����. � ��� ������� ��� �������� ������
int SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string& searchSymbol, int context) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
    int userChoice;
    string path = "";
    int errorCode = NoError;
    do {
        system("cls");
        cout << "������� ���� � �����: ";
        cin >> path;
        if (ifstream(path)) {
            PrintAdditionalMenu(); // ����� ���������������� ����
            MenuInputCheck(&userChoice, RewriteMenuItem, GoBackMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // ������� � �����������
               //////////////
                switch (context) { // TODO: ������ ����� ��� ��� ���� ����� ������
                case SaveResultContext: { // ���������� �����������
                    PrintResultInFile(text, wordsWithSearchSymbol, searchSymbol, path);
                    break; }
                case SaveInitialDataContext: { // ���������� �������� ������
                    PrintInitialDataInFile(text, searchSymbol, path);
                    break; }
                }
                break;
                ////////////////

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
        else {
            int errorCode = PathInput(path, SaveContext);
            //ofstream fout(path, ofstream::app);
            //error_code ec;
            //if (!is_regular_file(path, ec)) {
            //    cout << "����� �������� ������������ ��������. ��������� ����." << endl;
            //    continue;
            //}
            //if (!fout) {
            //    cout << "������ ���������. ��������� ����." << endl;
            //    fout.close();
            //    continue;
            //}
            //fout.close();
            ////////////////////////////////////////////////////
            //fout.open(path, ofstream::trunc);
            switch (context) { // TODO: ������ ����� ��� ��� ���� ����� ������
            case SaveResultContext: { // ���������� �����������
                PrintResultInFile(text, wordsWithSearchSymbol, searchSymbol, path);
                break; }
            case SaveInitialDataContext: { // ���������� �������� ������
                PrintInitialDataInFile(text, searchSymbol, path);
                break; }
            }
        }
        //fout.close();
        cout << "������ ������� ���������." << endl;
        system("pause");

    } while (errorCode != NoError);
    return errorCode; // TODO: �� ���� ��� � ������������� ������� ����������, �� ����� � � ���������� SAVEDATA ��������. SAVEFILE ������� VOID
    //int errorCode = PathInput(path, SaveContext);
    //if (errorCode == NoError) {
    //    fstream fout(path);
    //    if (exists(path)) { // ���� ���� ��� ����������
    //        PrintAdditionalMenu(); // ����� ���������������� ����
    //        MenuInputCheck(&userChoice, RewriteMenuItem, GoBackMenuItem);
    //        switch (userChoice) {
    //        case RewriteMenuItem: { // ������� � �����������
    //            switch (context) {
    //            case SaveResultContext: { // ���������� �����������
    //                PrintResultInFile(text, wordsWithSearchSymbol, searchSymbol, path);
    //                break; }
    //            case SaveInitialDataContext: { // ���������� �������� ������
    //                PrintInitialDataInFile(text, searchSymbol, path);
    //                break; }
    //            }
    //            break;
    //        }
    //        case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
    //            SaveFile(text, wordsWithSearchSymbol, searchSymbol, context);
    //            break;
    //        }
    //        case GoBackMenuItem: { // ����� � ������� ����
    //            Menu();
    //            break; }
    //        }
    //    }

    //    if (!exists(path)) { // ���� ����� ��� �� ���������� �� ������� ����
    //        switch (context) {
    //        case SaveResultContext: { // ���������� �����������
    //            PrintResultInFile(text, wordsWithSearchSymbol, searchSymbol, path);
    //            break; }
    //        case SaveInitialDataContext: { // ���������� �������� ������
    //            PrintInitialDataInFile(text, searchSymbol, path);
    //            break; }
    //        }
    //    }
    //    fout.close();
    //    cout << "������ ������� ���������." << endl;
    //    system("pause");
    //    return NoError;
    //}
    //else {
    //    return ErrorInFileFuncs;
    //}
}