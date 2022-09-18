#pragma once
#include <vector>
#include <string>

void MenuInputCheck(int* userChoice, const int min, const int max);

void Greeting();

void PrintMenu();

void PrintYesNoMenu(const std::string msg);

void PrintErrorMenu();

void PrintText(const std::vector<std::string>& text, const std::string& searchSymbol);

void PrintResult(const std::vector<std::string>& wordsWithSearchSymbol);

void Menu();

int ManualInput(std::vector<std::string>& text, std::string& searchSymbol);

int SaveData(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol);

enum Menu { ManualInputMenuItem = 1, InputFromFileMenuItem, ShowInfoMenuItem, UnitTestMenuItem, ExitMenuItem };

enum SaveAnswer { Yes = 1, No };

enum Context { SaveResultContext = 1, SaveInitialDataContext, SaveContext, InputContext };