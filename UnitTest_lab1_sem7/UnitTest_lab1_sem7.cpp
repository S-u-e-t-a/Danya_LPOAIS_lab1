#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1_sem7/textFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestlab1sem7
{
  TEST_CLASS(UnitTestlab1sem7)
  {
  public:

    //void FindSymbolInText(std::vector<std::string>&wordsWithSearchSymbol, std::string searchSymbol);
#pragma region SplitTextTests
    TEST_METHOD(TestMethod1)
    {
      vector<string> testText = { "test1 test2\t test3. test4" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> excpetced = { "test1", "test2", "test3", "test4" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod2)
    {
      vector<string> testText = { "test1.../!@$%^test2" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> excpetced = { "test1", "test2" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod3)
    {
      vector<string> testText = { "test1\n test2\n test3\n test4" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> excpetced = { "test1", "test2", "test3", "test4" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod4)
    {
      vector<string> testText = { "t e s t		" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> excpetced = { "t", "e", "s", "t" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod5)
    {
      vector<string> testText = { "test1 @$ @# () [test2\t] + test3. -test4" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> excpetced = { "test1", "test2", "test3", "test4" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod6)
    {
      vector<string> testText = { "10+11=21\n 9 + 10 = 21" };
      vector<string> actual;
      SplitText(testText, actual);
      vector<string> excpetced = { "10", "11", "21", "9", "10", "21" };
      Assert::AreEqual(excpetced, actual);
    }
#pragma endregion

#pragma region FindSymbolInTextTests
    TEST_METHOD(TestMethod7)
    {
      vector<string> actual = { "test1", "test2", "test3", "test4" };
      string searchSymbol = "1";
      //vector<string> actual;
      FindSymbolInText(actual, searchSymbol);
      vector<string> excpetced = { "test1" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod8)
    {
      vector<string> actual = { "test1", "teest2", "test3", "test4" };
      string searchSymbol = "ee";
      //vector<string> actual;
      FindSymbolInText(actual, searchSymbol);
      vector<string> excpetced = { "teest2" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod9)
    {
      vector<string> actual = { "test", "toast", "least", "beast" };
      string searchSymbol = "as";
      //vector<string> actual;
      FindSymbolInText(actual, searchSymbol);
      vector<string> excpetced = { "toast", "beast"};
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod10)
    {
      vector<string> actual = { "12", "34", "56", "78", "t3st", "7es7", "te5t", "7357"};
      string searchSymbol = "1";
      //vector<string> actual;
      FindSymbolInText(actual, searchSymbol);
      vector<string> excpetced = { "7" };
      Assert::AreEqual(excpetced, actual);
    }
    TEST_METHOD(TestMethod11)
    {
      vector<string> actual = { "test1", "test2", "test3", "test4" };
      string searchSymbol = "1";
      //vector<string> actual;
      FindSymbolInText(actual, searchSymbol);
      vector<string> excpetced = { "test1" };
      Assert::AreEqual(excpetced, actual);
    }
#pragma endregion
  };
}
