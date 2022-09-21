#pragma once
#include <vector>
#include <string>

void MenuInputCheck(int* userChoice, const int min, const int max);

void Greeting();

void PrintMenu();

void PrintYesNoMenu(const std::string& msg);

void PrintErrorMenu();

void PrintText(const std::vector<std::string>& text, const std::string& searchSymbol);

void PrintResult(const std::vector<std::string>& wordsWithSearchSymbol);

void PrintWarning();

void CreateText(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol, std::vector<std::string>& createdText, int context);

void Menu();

void ManualInput(std::vector<std::string>& text, std::string& searchSymbol);

void SaveData(const std::vector<std::string>& text);

enum Menu { NoMenuItem = 0, ManualInputMenuItem, InputFromFileMenuItem, ShowInfoMenuItem, ExitMenuItem };

enum SaveAnswer { Yes = 1, No };

enum Context { SaveResultContext = 1, SaveInitialDataContext, SaveContext, InputContext };