#include <iostream>
using namespace std;

class WrongChoiceException : public exception // Исключение для неправильного выбора пункта меню
{
public:
  WrongChoiceException(const char* msg, int* dataState, int min, int max) : exception(msg) // Конструктор исключения
  {
    this->dataState = dataState;
    this->min = min;
    this->max = max;
  }
  int* GetDataState()
  {
    return dataState;
  }
  int GetMin()
  {
    return min;
  }
  int GetMax()
  {
    return max;
  }
private:
  int* dataState;
  int min;
  int max;
};

class WrongPathInput : public exception // Исключение для неправильного указания пути или имени файла
{
public:
  WrongPathInput(const char* msg, string dataState) : exception(msg) // Конструктор исключения
  {
    this->dataState = dataState;
  }
  string GetDataState()
  {
    return dataState;
  }
private:
  string dataState;
};

class FileIsReadOnly : public exception // Исключение при сохранении в файл с атрибутом "только для чтения"
{
public:
  FileIsReadOnly(const char* msg) : exception(msg) // Конструктор исключения
  {
  }
}

// https:/iot-embedded.ru/programming_c_and_cpp/cpp-generiruem-svoi-iskljucheniya-svoj-kla/
// https:/radioprog.ru/post/1302