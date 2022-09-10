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

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, std::string path);

void PrintInitialData(const std::vector<std::string>& text, std::string path);

std::vector<std::string> FileInput(std::vector<std::string>& text);

void SaveResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol);

void SaveInitialData(const std::vector<std::string>& text);

enum Saving { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };
