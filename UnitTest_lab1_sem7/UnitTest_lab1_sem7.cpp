#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1_sem7/textFunctions.h"
#include "../lab1_sem7/textFunctions.cpp"

//namespace Microsoft {
//  namespace VisualStudio {
//    namespace CppUnitTestFramework {
//      template <> static std::wstring ToString(const std::vector<std::string>& vec) {
//        std::wstringstream s;
//        for (int i = 0; i != vec.size(); i++) {
//          for (int j = 0; j != vec[i].size(); j++) {
//            s << vec[i][j];
//          }
//          s << " ";
//        }
//        return s.str();
//      }
//      //template <> static std::wstring ToString(const pair<double, double>& q) {
//      //  wstringstream s;
//      //  s << q.first << ' ' << q.second << ' ';
//      //  return s.str();
//      //}
//    }
//  }
//}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest_lab1_sem7
{
  TEST_CLASS(UnitTestlab1sem7)
  {
  public:
#pragma region SplitTextTests
    TEST_METHOD(SplitTextTest1)
    {
      vector<string> testText = { "test1 test2\t test3. test4" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> expected = { "test1", "test2", "test3", "test4" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(SplitTextTest2)
    {
      vector<string> testText = { "test1.../!@$%^test2" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> expected = { "test1", "test2" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(SplitTextTest3)
    {
      vector<string> testText = { "test1\n test2\n test3\n test4" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> expected = { "test1", "test2", "test3", "test4" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(SplitTextTest4)
    {
      vector<string> testText = { "t e s t		" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> expected = { "t", "e", "s", "t" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(SplitTextTest5)
    {
      vector<string> testText = { "test1 @$ @# () [test2\t] + test3. -test4" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> expected = { "test1", "test2", "test3", "test4" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(SplitTextTest6)
    {
      vector<string> testText = { "10+11=21\n 9 + 10 = 21" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> expected = { "10", "11", "21", "9", "10", "21" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
#pragma endregion

#pragma region FindSymbolInTextTests
    TEST_METHOD(FindSymbolInTextTest1)
    {
      vector<string> actual = { "test1", "test2", "test3", "test4" };
      string searchSymbol = "1";
      FindSymbolInText(actual, searchSymbol);
      vector<string> expected = { "test1" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(FindSymbolInTextTest2)
    {
      vector<string> actual = { "test1", "teest2", "test3", "test4" };
      string searchSymbol = "ee";
      FindSymbolInText(actual, searchSymbol);
      vector<string> expected = { "teest2" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(FindSymbolInTextTest3)
    {
      vector<string> actual = { "test", "toast", "least", "beast" };
      string searchSymbol = "as";
      FindSymbolInText(actual, searchSymbol);
      vector<string> expected = { "toast", "least", "beast" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(FindSymbolInTextTest4)
    {
      vector<string> actual = { "12", "34", "56", "78", "t3st", "7es7", "te5t", "7357" };
      string searchSymbol = "1";
      FindSymbolInText(actual, searchSymbol);
      vector<string> expected = { "12" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(FindSymbolInTextTest5)
    {
      vector<string> actual = { "12", "34", "56", "78", "t3st", "7es7", "te5t", "7357" };
      string searchSymbol = "7";
      FindSymbolInText(actual, searchSymbol);
      vector<string> expected = { "78", "7es7", "7357" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
    TEST_METHOD(FindSymbolInTextTest6)
    {
      vector<string> actual = { "test1", "test2", "test3", "test4" };
      string searchSymbol = "1";
      FindSymbolInText(actual, searchSymbol);
      vector<string> expected = { "test1" };
      //for (unsigned int i = 0; i < actual.size(); i++) {
      //  Assert::AreEqual(actual[i], expected[i]);
      //}
      //Assert::AreEqual(expected, actual);
      Assert::IsTrue(actual == expected);
    }
#pragma endregion
  };
}
