#pragma once
#include <vector>
#include <string>
#include <algorithm>

void SplitText(const std::vector<std::string>& text, std::vector<std::string>& wordsWithSearchSymbol);

size_t ConverToLower(std::string text, const std::string& searchSymbol, size_t pos);

void FindSymbolInText(std::vector<std::string>& wordsWithSearchSymbol, const std::string& searchSymbol);

enum Symbol { Number = 1, Separator, Word };
