#include "fileSystem.h"
#include "userInterface.h"
#include <Windows.h>

using namespace std::experimental::filesystem;
using namespace std;

bool CheckPath(string filename) { // �������� ����
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

bool CheckReadOnly(string filename) { // �������� ����� �� ������� "������ ��� ������"
	ifstream file(filename);
	WIN32_FIND_DATAA findData;
	LPCSTR name = filename.c_str();
	FindFirstFileA(name, &findData);
	if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
		cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
		return false;
	}
	else return true;
}

int AdditionalMenu() { // ��������������� ����, ���� � ���� ���������� ����� ��� ��������� ��� ������������ ����. ���������� ������������ ���� ��� ������� ������ ���� � ����� ������
	int variant;
	cout << endl;
	cout << "\t�������� �������:" << endl;
	cout << "1. ������������ ����." << endl;
	cout << "2. ������� ����� ����." << endl;
	variant = InputCheck();
	bool variant_is_correct = false;
	while (variant_is_correct == false) {
		if (variant >= Rewrite && variant <= CreateNewFile) {
			variant_is_correct = true;
		}
		else {
			cerr << "���� �����������, ���������� �����: ";
			variant = InputCheck();
		}
	}
	cout << endl;
	return variant;
}

void PrintResult(const vector<string>& text, const vector<string>& redacted_text, string line_for_search, int counter, string path) { // ��������������� ������� ��� ������ ������ � ����
	ofstream fout(path);
	fout << "�������� �����: " << endl;
	fout << endl;
	for (int i = 0; i < text.size(); i++) {
		fout << text[i] << endl;
	}
	fout << endl;
	if (text != redacted_text) {
		fout << "����� ����� ��������������: " << endl;
		fout << endl;
		for (int i = 0; i < redacted_text.size(); i++) {
			fout << redacted_text[i] << endl;
		}
		fout << endl;
	}
	//if (stats.symbols != 0 || stats.words != 0 || stats.lines != 0 || stats.paragraphs != 0) {
	//	fout << "���������� ��������: " << stats.symbols << endl;
	//	fout << "���������� ����: " << stats.words << endl;
	//	fout << "���������� �����: " << stats.lines << endl;
	//	fout << "���������� �������: " << stats.paragraphs << endl;
	//}
	if (line_for_search != "") {
		fout << "��������� ��� ������: " << line_for_search << endl;
		fout << endl;
		fout << "������ ������ ����������� " << counter << " ���(�)." << endl;
	}
}

void PrintInitialData(const vector<string>& text, string path) { // ������� ��� ������ �������� ������ � ����
	ofstream fout(path);
	for (int i = 0; i < text.size(); i++) {
		fout << text[i] << endl;
	}
}

vector<string> FileInput(vector<string>& text) { // ������� ��� ������ ������ �� �����
	string path_input;
	cout << "������� ���� � �����: ";
	getline(cin, path_input);
	ifstream fin(path_input);
	while (true) {
		while (!fin || CheckPath(path_input)) { // �������� �� ������������� ����� �� ���������� ����
			fin.close();
			cerr << "������������ �������� ���� ��� ����� �����." << endl;
			cout << "������� ���� � �����: ";
			getline(cin, path_input);
			fin.open(path_input); // �������� �����
			cout << endl;
		}
		break;
	}
	fin.seekg(0, ios::beg);
	string temp; // ���������� ��� ���������� �������� �������� �� �����
	while (!fin.eof()) {
		while (getline(fin, temp))
			text.push_back(temp);
	}
	fin.close();
	return text;
}

void SaveResult(const vector<string>& text, const vector<string>& redacted_text, amount_in_text stats, string line_for_search, int counter) { // ������� ��� ���������� ���������� � ����
	string path_output;
	cout << "������� ���� � �����: ";
	getline(cin, path_output);
	ifstream fout(path_output);
	while (CheckPath(path_output) || !CheckReadOnly(path_output)) { // �������� �� ���������� ���� � ��� �����
		fout.close();
		cerr << "������������ �������� ���� ��� ����� �����." << endl;
		cout << "������� ���� � �����: ";
		getline(cin, path_output);
		fout.open(path_output);
	}
	cout << endl;
	fout.close();
	while (fout) { // ���� ���� ��� ����������
		cout << endl;
		cout << "������ ���� ��� ����������." << endl;
		int choice = AdditionalMenu(); // ����� ���������������� ����
		switch (choice) {
		case Rewrite: { // ������� � �����������
			ofstream fout(path_output);
			PrintResult(text, redacted_text, stats, line_for_search, counter, path_output);
			fout.close();
			break; }
		case CreateNewFile: { // ������� � ��������� ������ �����
			fout.close();
			SaveResult(text, redacted_text, stats, line_for_search, counter);
			break;
		}
		}
		break;
	}
	if (!fout) { // ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
		PrintResult(text, redacted_text, stats, line_for_search, counter, path_output);
		fout.close();
	}
}

void SaveInitialData(const vector<string>& text) {  // ������� ��� ������ �������� ������ � ����
	string path_output;
	cout << "������� ���� � �����: ";
	getline(cin, path_output);
	ifstream fout(path_output);
	while (CheckPath(path_output) || !CheckReadOnly(path_output)) { // �������� �� ���������� ���� � ��� �����
		fout.close();
		cerr << "������������ �������� ���� ��� ����� �����." << endl;
		cout << "������� ���� � �����: ";
		getline(cin, path_output);
		fout.open(path_output);
	}
	cout << endl;
	fout.close();
	while (fout) { // ���� ���� ��� ����������
		cout << endl;
		cout << "������ ���� ��� ����������." << endl;
		int choice = AdditionalMenu(); // ����� ���������������� ����
		switch (choice) {
		case Rewrite: { // ������� � �����������
			ofstream fout(path_output);
			PrintInitialData(text, path_output);
			fout.close();
			break; }
		case CreateNewFile: { // ������� � ��������� ������ �����
			fout.close();
			SaveInitialData(text);
			break; }
		}
		break;
	}
	if (!fout) { // ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
		PrintInitialData(text, path_output);
		fout.close();
	}
	cout << endl;
}