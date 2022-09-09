#pragma once
#include <vector>
#include <string>

void Greeting();

int InputCheck();

void Menu();

void SaveData(const std::vector<std::string>& text, const std::vector<std::string>& redacted_text, std::string line_for_search, int counter);

enum Menu { ManualInputMenuItem = 1, InputFromFileMenuItem, ShowInfoMenuItem, UnitTestMenuItem, ExitMenuItem };

enum Save_Answer { Yes = 1, No };
