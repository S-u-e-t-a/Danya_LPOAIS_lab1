#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <string>

void PrintAdditionalMenu();

bool CheckPath(std::string path);

bool CheckReadOnly(std::string filename);

void PrintResult(const std::vector<std::string>& text, const std::vector<std::string>& redacted_text, std::string line_for_search, std::string path);

void PrintInitialData(const std::vector<std::string>& text, std::string path);

std::vector<std::string> FileInput(std::vector<std::string>& text);

void SaveResult(const std::vector<std::string>& text, const std::vector<std::string>& redacted_text, std::string line_for_search);

void SaveInitialData(const std::vector<std::string>& text);

enum Saving { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };
