#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

using namespace std::experimental::filesystem;
using namespace std;

bool CheckPath(string filename) { // Проверка пути
	size_t found = filename.find_last_of("\\");
	size_t point = filename.find_last_of(".");
	size_t base = point - found - 1;
	string basefilenameStr = filename.substr(found + 1, base);
	const char* basefilenameChar = basefilenameStr.c_str();
	ofstream file(filename, ios::app);
	if (!_strcmpi(basefilenameChar, "con")) return true;
	//if (!is_regular_file(filename)) return true;
	file.close();
	return false;
}

bool CheckReadOnly(string filename) { // Проверка файла на атрибут "только для чтения"
	ifstream file(filename);
	WIN32_FIND_DATAA findData;
	LPCSTR name = filename.c_str();
	FindFirstFileA(name, &findData);
	if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
		cerr << "Невозможно сохранить данные в файл, предназначенный только для чтения." << endl;
		return false;
	}
	else return true;
}

int AdditionalMenu() { // Вспомогательное меню, если в ходе сохранения файла был обнаружен уже существующий файл. Предлагает перезаписать файл или создать другой файл с новым именем
	int variant;
	cout << endl;
	cout << "\tВыберите вариант:" << endl;
	cout << "1. Перезаписать файл." << endl;
	cout << "2. Создать новый файл." << endl;
	variant = InputCheck();
	bool variant_is_correct = false;
	while (variant_is_correct == false) {
		if (variant >= Rewrite && variant <= CreateNewFile) {
			variant_is_correct = true;
		}
		else {
			cerr << "Ввод некорректен, попробуйте снова: ";
			variant = InputCheck();
		}
	}
	cout << endl;
	return variant;
}

void PrintResult(const vector<string>& text, const vector<string>& redacted_text, string line_for_search, int counter, string path) { // Вспомогательная функция для записи данных в файл
	ofstream fout(path);
	fout << "Исходный текст: " << endl;
	fout << endl;
	for (int i = 0; i < text.size(); i++) {
		fout << text[i] << endl;
	}
	fout << endl;
	if (text != redacted_text) {
		fout << "Текст после редактирования: " << endl;
		fout << endl;
		for (int i = 0; i < redacted_text.size(); i++) {
			fout << redacted_text[i] << endl;
		}
		fout << endl;
	}
	//if (stats.symbols != 0 || stats.words != 0 || stats.lines != 0 || stats.paragraphs != 0) {
	//	fout << "Количество символов: " << stats.symbols << endl;
	//	fout << "Количество слов: " << stats.words << endl;
	//	fout << "Количество строк: " << stats.lines << endl;
	//	fout << "Количество абзацев: " << stats.paragraphs << endl;
	//}
	if (line_for_search != "") {
		fout << "Подстрока для поиска: " << line_for_search << endl;
		fout << endl;
		fout << "Данная строка встречается " << counter << " раз(а)." << endl;
	}
}

void PrintInitialData(const vector<string>& text, string path) { // Функция для вывода исходных данных в файл
	ofstream fout(path);
	for (int i = 0; i < text.size(); i++) {
		fout << text[i] << endl;
	}
}

vector<string> FileInput(vector<string>& text) { // Функция для чтения данных из файла
	string path_input;
	cout << "Введите путь к файлу: ";
	getline(cin, path_input);
	ifstream fin(path_input);
	while (true) {
		while (!fin || CheckPath(path_input)) { // Проверка на существование файла по указанному пути
			fin.close();
			cerr << "Некорректное указание пути или имени файла." << endl;
			cout << "Введите путь к файлу: ";
			getline(cin, path_input);
			fin.open(path_input); // Открытие файла
			cout << endl;
		}
		break;
	}
	fin.seekg(0, ios::beg);
	string temp; // Переменная для временного хранения символов из файла
	while (!fin.eof()) {
		while (getline(fin, temp))
			text.push_back(temp);
	}
	fin.close();
	return text;
}

void SaveResult(const vector<string>& text, const vector<string>& redacted_text, amount_in_text stats, string line_for_search, int counter) { // Функция для сохранения результата в файл
	string path_output;
	cout << "Введите путь к файлу: ";
	getline(cin, path_output);
	ifstream fout(path_output);
	while (CheckPath(path_output) || !CheckReadOnly(path_output)) { // Проверка на корректный путь и имя файла
		fout.close();
		cerr << "Некорректное указание пути или имени файла." << endl;
		cout << "Введите путь к файлу: ";
		getline(cin, path_output);
		fout.open(path_output);
	}
	cout << endl;
	fout.close();
	while (fout) { // Если файл уже существует
		cout << endl;
		cout << "Данный файл уже существует." << endl;
		int choice = AdditionalMenu(); // Вывод вспомогательного меню
		switch (choice) {
		case Rewrite: { // Вариант с перезаписью
			ofstream fout(path_output);
			PrintResult(text, redacted_text, stats, line_for_search, counter, path_output);
			fout.close();
			break; }
		case CreateNewFile: { // Вариант с созданием нового файла
			fout.close();
			SaveResult(text, redacted_text, stats, line_for_search, counter);
			break;
		}
		}
		break;
	}
	if (!fout) { // Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
		PrintResult(text, redacted_text, stats, line_for_search, counter, path_output);
		fout.close();
	}
}

void SaveInitialData(const vector<string>& text) {  // Функция для записи исходных данных в файл
	string path_output;
	cout << "Введите путь к файлу: ";
	getline(cin, path_output);
	ifstream fout(path_output);
	while (CheckPath(path_output) || !CheckReadOnly(path_output)) { // Проверка на корректный путь и имя файла
		fout.close();
		cerr << "Некорректное указание пути или имени файла." << endl;
		cout << "Введите путь к файлу: ";
		getline(cin, path_output);
		fout.open(path_output);
	}
	cout << endl;
	fout.close();
	while (fout) { // Если файл уже существует
		cout << endl;
		cout << "Данный файл уже существует." << endl;
		int choice = AdditionalMenu(); // Вывод вспомогательного меню
		switch (choice) {
		case Rewrite: { // Вариант с перезаписью
			ofstream fout(path_output);
			PrintInitialData(text, path_output);
			fout.close();
			break; }
		case CreateNewFile: { // Вариант с созданием нового файла
			fout.close();
			SaveInitialData(text);
			break; }
		}
		break;
	}
	if (!fout) { // Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
		PrintInitialData(text, path_output);
		fout.close();
	}
	cout << endl;
}