#pragma once
#include <vector>
#include <string>
#include <algorithm>

void SplitText(const std::vector<std::string>& text, std::vector<std::string>& wordsWithSearchSymbol);

void FindSymbolInText(std::vector<std::string>& wordsWithSearchSymbol, std::string searchSymbol);

//size_t ConvertToLower(std::string text, const std::string& searchSymbol, size_t pos);
//
//int SearchForString(const vector<string>& text, const string searchSymbol);

enum Symbol { Number = 1, Separator, Word };
