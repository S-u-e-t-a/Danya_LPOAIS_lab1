// main.cpp
// Лабораторная работа № 1.
// Вариант 5.
// Работа с символьными строками.
// Задан текст. Распечатать все слова, содержащие заданный символ.
#include <iostream>
#include "userInterface.h"
#define NOMINMAX
#include <cstdlib>
#include <windows.h>

using namespace std;

int main() {
    system("color F0");
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Greeting();
    while (true) {
        Menu();
    }
}