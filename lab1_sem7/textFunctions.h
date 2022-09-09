#pragma once
#include <vector>
#include <string>
#include <algorithm>

size_t ConvertToLower(std::string text, std::string line_for_search, size_t pos);

int SearchForString(const std::vector<std::string>& text, std::string string_for_copy);

std::vector<std::string> CopyString(std::vector<std::string>& text, int number_of_string_for_copy, int number_of_string);

enum Symbol { Number = 1, Separator, Word };
