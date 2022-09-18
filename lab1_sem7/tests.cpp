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
        cout << "Тест №1 провалился." << endl;
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
        cout << "Тест №2 провалился." << endl;
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
        cout << "Тест №3 провалился." << endl;
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
        cout << "Тест №4 провалился." << endl;
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
        cout << "Тест №5 провалился." << endl;
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
        cout << "Тест №6 провалился." << endl;
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
        cout << "Тест №7 провалился." << endl;
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
        cout << "Тест №8 провалился." << endl;
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
        cout << "Тест №9 провалился." << endl;
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
        cout << "Тест №10 провалился." << endl;
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
        cout << "Тест №10 провалился." << endl;
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
        cout << "Тест №11 провалился." << endl;
        cout << endl;
        count--;
    }
#pragma endregion

    if (count == NumberOfTests) { // Тест прошёл успешно
        cout << "Тестирование прошло успешно." << endl;
        system("pause");
    }
    else {
        cerr << "Тестирование провалилось." << endl;
        cout << "Возможные причины ошибки: " << endl;
        cout << "* Неверно введены ожидаемый результаты подсчёта" << endl;
        cout << "* Неверно введен исходный текст" << endl;
        cout << "* Неверно введен ожидаемый текст" << endl;
        system("pause");
    }
}