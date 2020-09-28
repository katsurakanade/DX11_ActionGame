#include "main.h"
#include "FileManger.h"
#include <iostream>
#include <fstream>

void FileManger::Read(const char* pass,float output[21][21]) {

	std::string filename = pass;
	std::ifstream file;

	file.open(filename);

	if (file.is_open()) {
		for (int i = 0; i < 21; i++) {
			for (int k = 0; k < 21; k++) {
				file >> output[i][k];
			}
		}

		file.close();
	}
}

void FileManger::Write(const char* pass, float output[21][21]) {

	std::string filename = pass;
	std::ofstream file;

	file.open(filename);
	assert(file);

	if (file.is_open()) {
		for (int i = 0; i < 21; i++) {
			for (int k = 0; k < 21; k++) {
				file << output[i][k] << std::endl;
			}
		}
		file.close();
		MessageBox(GetWindow(), "セーブ成功", "マップデータ", MB_ICONINFORMATION);
	}
}


