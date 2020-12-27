/*
ファイルIOクラス
*/
#pragma once

#include "Grass.h"
#include "Particle.h"
#include "Lib/nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

typedef struct
{
	BYTE b;
	BYTE g;
	BYTE r;
}RGB;

class FileManager
{

private:



public:

	// 高さマップ読み込み
	static void ReadImageMap(const char* pass, float output[FIELD_X][FIELD_X]);
	// パーティクル情報作成
	static void CreateParticleJSON(const char* pass, ParitcleSetting* setting);
	// パーティクル情報読み込み
	static ParitcleSetting ReadParticleJSON(const char* pass);

	// リソースIO
	static void ReadResource(const char* pass);
	template <typename T> 
	static void WriteResource(const char* pass, std::vector <T*> resource) {
		std::string filename = pass;
		std::ofstream file;

		file.open(filename);
		assert(file);

		if (file.is_open()) {
			file << resource.size() << std::endl;
			for (unsigned int i = 0; i < resource.size(); i++) {

				json data;
				data["Name"] = resource[i]->Name;
				data["Type"] = resource[i]->Type;
				data["Tag"] = resource[i]->Tag;
				data["Position"]["x"] = resource[i]->Position.x;
				data["Position"]["y"] = resource[i]->Position.y;
				data["Position"]["z"] = resource[i]->Position.z;
				data["Rotation"]["x"] = resource[i]->Rotation.x;
				data["Rotation"]["y"] = resource[i]->Rotation.y;
				data["Rotation"]["z"] = resource[i]->Rotation.z;
				data["Scale"]["x"] = resource[i]->Scale.x;
				data["Scale"]["y"] = resource[i]->Scale.y;
				data["Scale"]["z"] = resource[i]->Scale.z;

				file << data << std::endl;
			}
			file.close();
			MessageBox(GetWindow(), "セーブ成功", "リソースデータ", MB_ICONINFORMATION);
		}
	}


};