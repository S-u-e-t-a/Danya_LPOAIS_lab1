#include <iostream>
using namespace std;

class WrongChoiceException : public exception
{
public:
  WrongChoiceException(char* msg, int dataState) : exception(msg) // Конструктор исключения
  {
    this->dataState = dataState;
  }
  int GetDataState()
  {
    return dataState;
  }
private:
  int dataState;
};

// https://iot-embedded.ru/programming_c_and_cpp/cpp-generiruem-svoi-iskljucheniya-svoj-kla/
// https://radioprog.ru/post/1302