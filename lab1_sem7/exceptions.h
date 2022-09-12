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
  WrongPathInput(const char* msg, string dataState, int context) : exception(msg) // ����������� ����������
  {
    this->dataState = dataState;
    this->context = context;
  }
  string GetDataState()
  {
    return dataState;
  }
  int GetContext()
  {
    return context;
  }
private:
  string dataState;
  int context;
};

class FileIsReadOnly : public exception // ���������� ��� ���������� � ���� � ��������� "������ ��� ������"
{
public:
  FileIsReadOnly(const char* msg, int context) : exception(msg) // ����������� ����������
  {
    this->context = context;
  }
  int GetContext()
  {
    return context;
  }
private:
  int context;
};