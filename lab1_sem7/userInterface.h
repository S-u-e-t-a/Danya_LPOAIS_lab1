#pragma once
#include <vector>
#include <string>

void MenuInputCheck(int* userChoice, int min, int max);

void Greeting();

void PrintMenu();

void PrintYesNoMenu(std::string msg);

void PrintErrorMenu();

void Menu();

void ManualInput(std::vector<std::string>& text, std::string& searchSymbol);

void SaveData(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol);

enum Menu { ManualInputMenuItem = 1, InputFromFileMenuItem, ShowInfoMenuItem, UnitTestMenuItem, ExitMenuItem };

enum SaveAnswer { Yes = 1, No };

enum Context { SaveResultContext = 1, SaveInitialDataContext, InputContext };
