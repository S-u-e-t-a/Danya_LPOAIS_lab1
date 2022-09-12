#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <string>

void PrintAdditionalMenu();

void CheckPath(std::string path); // ьс void

void CheckReadOnly(std::string filename); // ьс void

void PrintResult(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, std::string path);

void PrintErrorMenu();

void PrintInitialData(const std::vector<std::string>& text, std::string path);

void FileInput(std::vector<std::string>& text);

void SaveFile(const vector<string>& text, const vector<string>& wordsWithSearchSymbol, string searchSymbol, int saveContext);

enum SavingMenuItems { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackMenuItem };

enum ErrorMenuItems { EnterDataAgainMenuItem = 1, GoBackMenuItem };
