#include <iostream>
using namespace std;

class WrongChoiceException : public exception // ���������� ��� ������������� ������ ������ ����
{
public:
  WrongChoiceException(const char* msg, int* dataState, int min, int max) : exception(msg) // ����������� ����������
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

class WrongPathInput : public exception // ���������� ��� ������������� �������� ���� ��� ����� �����
{
public:
  WrongPathInput(const char* msg, string dataState) : exception(msg) // ����������� ����������
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

class FileIsReadOnly : public exception // ���������� ��� ���������� � ���� � ��������� "������ ��� ������"
{
public:
  FileIsReadOnly(const char* msg) : exception(msg) // ����������� ����������
  {
  }
}

// https:/iot-embedded.ru/programming_c_and_cpp/cpp-generiruem-svoi-iskljucheniya-svoj-kla/
// https:/radioprog.ru/post/1302