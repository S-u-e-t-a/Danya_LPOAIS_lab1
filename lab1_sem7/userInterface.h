#pragma once
#include <vector>
#include <string>

void MenuInputCheck(int* userChoice, int min, int max);

void Greeting();

void PrintMenu();

void Menu();

void ManualInput(vector<string> text, char* searchSymbol);

void SaveData(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol);

enum Menu { ManualInputMenuItem = 1, InputFromFileMenuItem, ShowInfoMenuItem, UnitTestMenuItem, ExitMenuItem };

enum SaveAnswer { Yes = 1, No };

enum MenuContext { SaveResultContext = 1, SaveInitialDataContext };
