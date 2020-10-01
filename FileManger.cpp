#include "main.h"
#include "FileManger.h"
#include "Application.h"
#include "Scene.h"
#include "Lib/nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

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

void FileManger::ReadResource(const char* pass) {

	std::string filename = pass;
	std::ifstream file;
	int length;

	file.open(filename);

	if (file.is_open()) {
		file >> length;
		
		for (int i = 0; i < length; i++) {

			json data;
			Resource* g = Application::GetScene()->AddGameObject<Grass>(EffectLayer);
			D3DXVECTOR3 pos,rot,scl;
			file >> data;
			g->Name = data["Name"];
			g->Position.x = data["Position"]["x"];
			g->Position.y = data["Position"]["y"];
			g->Position.z = data["Position"]["z"];
			g->Rotation.x = data["Rotation"]["x"];
			g->Rotation.y = data["Rotation"]["y"];
			g->Rotation.z = data["Rotation"]["z"];
			g->Scale.x = data["Scale"]["x"];
			g->Scale.y = data["Scale"]["y"];
			g->Scale.z = data["Scale"]["z"];
		}

		file.close();
	}
}

