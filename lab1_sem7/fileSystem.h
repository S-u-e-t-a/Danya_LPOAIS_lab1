#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <string>

void PrintAdditionalMenu();

void CheckPath(std::string path, int context);

void CheckReadOnly(std::string filename, int context);

void PathInput(std::string path, int context);

void PrintAdditionalMenu();

void PrintResult(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol, std::string& path);

void PrintInitialData(const std::vector<std::string>& text, std::string& path);

void FileInput(std::vector<std::string>& text, std::string& searchSymbol);

void SaveFile(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol, int saveContext);

enum SavingMenuItems { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };

enum ErrorMenuItems { EnterDataAgainMenuItem = 1, GoBackToMainMenuMenuItem };
