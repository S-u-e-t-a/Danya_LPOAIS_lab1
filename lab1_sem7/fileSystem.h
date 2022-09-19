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

int PathInput(std::string& path, int context);

void PrintResultInFile(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol, std::string& path);

void PrintInitialDataInFile(const std::vector<std::string>& text, std::string& path);

void FileInput(std::vector<std::string>& text, std::string& searchSymbol);

int SaveFile(const std::vector<std::string>& text, const std::vector<std::string>& wordsWithSearchSymbol, std::string& searchSymbol, int saveContext);

enum SavingMenuItems { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };

enum ErrorMenuItems { EnterDataAgainMenuItem = 1, GoBackToMainMenuMenuItem };

enum ErrorCodes { NoError, ErrorInPathInput, ErrorInFileFuncs };