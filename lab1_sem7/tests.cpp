#include <iostream>
#include "textFunctions.h"

using namespace std;

const int NumberOfTests = 12;

void RunModuleTests() {
    int count = 12;
#pragma region SplitTextUnitTest1
    vector<string> testText = { "test1 test2\t test3. test4" };
    vector<string> actual;
    SplitText(testText, actual);
    vector<string> expected = { "test1", "test2", "test3", "test4" };
    if (actual != expected) {
        cout << "���� �1 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region SplitTextUnitTest2
    testText = { "test1.../!@$%^test2" };
    actual.clear();
    SplitText(testText, actual);
    expected = { "test1", "test2" };
    if (actual != expected) {
        cout << "���� �2 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region SplitTextUnitTest3
    testText = { "test1\n test2\n test3\n test4" };
    actual.clear();
    SplitText(testText, actual);
    expected = { "test1", "test2", "test3", "test4" };
    if (actual != expected) {
        cout << "���� �3 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region SplitTextUnitTest4
    testText = { "t e s t		" };
    actual.clear();
    SplitText(testText, actual);
    expected = { "t", "e", "s", "t" };
    if (actual != expected) {
        cout << "���� �4 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region SplitTextUnitTest5
    testText = { "test1 @$ @# () [test2\t] + test3. -test4" };
    actual.clear();
    SplitText(testText, actual);
    expected = { "test1", "test2", "test3", "test4" };
    if (actual != expected) {
        cout << "���� �5 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region SplitTextUnitTest6
    testText = { "10+11=21\n 9 + 10 = 21" };
    actual.clear();
    SplitText(testText, actual);
    expected = { "10", "11", "21", "9", "10", "21" };
    if (actual != expected) {
        cout << "���� �6 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion  

#pragma region FindSymbolInTextUnitTest1
    actual = { "test1", "test2", "test3", "test4" };
    string searchSymbol = "1";
    FindSymbolInText(actual, searchSymbol);
    expected = { "test1" };
    if (actual != expected) {
        cout << "���� �7 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region FindSymbolInTextUnitTest2
    actual = { "test1", "teest2", "test3", "test4" };
    searchSymbol = "ee";
    FindSymbolInText(actual, searchSymbol);
    expected = { "teest2" };
    if (actual != expected) {
        cout << "���� �8 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region FindSymbolInTextUnitTest3
    actual = { "test", "toast", "least", "beast" };
    searchSymbol = "as";
    FindSymbolInText(actual, searchSymbol);
    expected = { "toast", "least", "beast" };
    if (actual != expected) {
        cout << "���� �9 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region FindSymbolInTextUnitTest4
    actual = { "12", "34", "56", "78", "t3st", "7es7", "te5t", "7357" };
    searchSymbol = "1";
    FindSymbolInText(actual, searchSymbol);
    expected = { "12" };
    if (actual != expected) {
        cout << "���� �10 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region FindSymbolInTextUnitTest5
    actual = { "12", "34", "56", "78", "t3st", "7es7", "te5t", "7357" };
    searchSymbol = "7";
    FindSymbolInText(actual, searchSymbol);
    expected = { "78", "7es7", "7357" };
    if (actual != expected) {
        cout << "���� �10 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

#pragma region FindSymbolInTextUnitTest6
    actual = { "test1", "test2", "test3", "test4" };
    searchSymbol = "1";
    FindSymbolInText(actual, searchSymbol);
    expected = { "test1" };
    if (actual != expected) {
        cout << "���� �11 ����������." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

    if (count == NumberOfTests) { // ���� ������ �������
        cout << "������������ ������ �������." << endl;
        system("pause");
    }
    else {
        cerr << "������������ �����������." << endl;
        cout << "��������� ������� ������: " << endl;
        cout << "* ������� ������� ��������� ���������� ��������" << endl;
        cout << "* ������� ������ �������� �����" << endl;
        cout << "* ������� ������ ��������� �����" << endl;
        system("pause");
    }
}