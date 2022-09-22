#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

void PrintAdditionalMenu();

bool IsPathIncorrect(const std::string path, const int context);

bool IsReadOnly(const std::string filename);

int CheckPath(const std::string& path, const int context);

int CheckData(const std::vector<std::string>& text, const std::string& searchSymbol);

void PrintTextInFile(const std::vector<std::string>& text, const std::string& path);

void ReadFromFile(std::vector<std::string>& text, std::string& searchSymbol, const std::string& path);

int FileInput(std::vector<std::string>& text, std::string& searchSymbol);

int SaveFile(const std::vector<std::string>& text);

enum SavingMenuItems { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };

enum ErrorMenuItems { EnterDataAgainMenuItem = 1, GoBackToMainMenuMenuItem };

enum ErrorCodes { NoError, ErrorInPathInput, ErrorInFileData, ErrorInTextInput, ErrorInSymbolInput, GoBack };