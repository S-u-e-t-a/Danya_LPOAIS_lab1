#pragma once
#include <vector>
#include <string>
#include <algorithm>

bool ContainSeparators(const std::vector<char> separators, const char symbol);

void SplitText(const std::vector<std::string>& text, std::vector<std::string>& wordsWithSearchSymbol);

void FindSymbolInText(std::vector<std::string>& wordsWithSearchSymbol, std::string searchSymbol);
