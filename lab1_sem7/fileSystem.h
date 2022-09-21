#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

void PrintAdditionalMenu();

bool IsPathIncorrect(std::string path, int context);

bool IsReadOnly(std::string filename);

int CheckPath(std::string& path, int context);

void PrintTextInFile(const std::vector<std::string>& text, std::string& path);

void ReadFromFile(std::vector<std::string>& text, std::string& searchSymbol, const std::string& path);

void FileInput(std::vector<std::string>& text, std::string& searchSymbol);

void SaveFile(const std::vector<std::string>& text);

enum SavingMenuItems { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };

enum ErrorMenuItems { EnterDataAgainMenuItem = 1, GoBackToMainMenuMenuItem };

enum ErrorCodes { NoError, ErrorInPathInput };