// main.cpp
// Лабораторная работа № 4.
// Работа с символьными строками
// Поиск заданной подстроки в тексте. Подсчет числа вхождений.
// Копирование строк.
// Подсчет количества символов, слов, строк, абзацев в тексте.
#include <iostream>
#include "userInterface.h"
#define NOMINMAX
#include <windows.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Greeting();
	while (true) {
		Menu();
	}
}