#include "main.h"
#include "Application.h"
#include "Scene.h"
#include "Props.h"
#include "ModelManager.h"

#include "Lib/nlohmann/json.hpp"
#include "FileManger.h"

using namespace std;
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>

void FileManager::ReadResource(const char* pass) {

	std::string filename = pass;
	std::ifstream file;
	int length;

	file.open(filename);

	if (file.is_open()) {
		file >> length;

		// サイズ <= 0
		if (length <= 0) {
			return;
		}
		
		for (int i = 0; i < length; i++) {	

			json data;
			file >> data;

			if (data["Type"] == "BillBoard") {
				Grass* g = nullptr;
				g = Application::GetScene()->AddGameObject<Grass>(EffectLayer);
				g->Name = data["Name"];
				g->Tag = data["Tag"];
				g->Position.x = data["Position"]["x"];
				g->Position.y = data["Position"]["y"];
				g->Position.z = data["Position"]["z"];
				g->Rotation.x = data["Rotation"]["x"];
				g->Rotation.y = data["Rotation"]["y"];
				g->Rotation.z = data["Rotation"]["z"];
				g->Scale.x = data["Scale"]["x"];
				g->Scale.y = data["Scale"]["y"];
				g->Scale.z = data["Scale"]["z"];

				if (data["Tag"] == "Grass") {
					g->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_GAME::PLANT));
				}
			}

			// Propsの場合
			else if (data["Type"] == "Object") {

				Props* p = nullptr;

				p = Application::GetScene()->AddGameObject<Props>(ObjectLayer);
				p->Name = data["Name"];
				p->Tag = data["Tag"];
				p->Position.x = data["Position"]["x"];
				p->Position.y = data["Position"]["y"];
				p->Position.z = data["Position"]["z"];
				p->Rotation.x = data["Rotation"]["x"];
				p->Rotation.y = data["Rotation"]["y"];
				p->Rotation.z = data["Rotation"]["z"];
				p->Scale.x = data["Scale"]["x"];
				p->Scale.y = data["Scale"]["y"];
				p->Scale.z = data["Scale"]["z"];

				if (data["Tag"] == "Rock") {
					if (p->GetComponent<ModelManager>()) {
						p->GetComponent<ModelManager>()->SetModel(Asset::GetInstance()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));
					}
				}

				else if (data["Tag"] == "Wall") {
					if (p->GetComponent<ModelManager>()) {
						p->GetComponent<ModelManager>()->SetModel(Asset::GetInstance()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::WALL));
					}
				}
			}
		

		}

		file.close();
	}
}

void FileManager::ReadImageMap(const char* pass, float output[FIELD_X][FIELD_X]) {

	Gdiplus::GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

	std::wstring infilename = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(pass);

	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(infilename.c_str());
	UINT height = bmp->GetHeight();
	UINT width = bmp->GetWidth();

	Gdiplus::Color color;

	for (UINT y = 0; y < height; y++)
		for (UINT x = 0; x < width; x++) {
			bmp->GetPixel(x, y, &color);
			output[y][x] = color.GetRed();
		}


	delete bmp;
	Gdiplus::GdiplusShutdown(gdiplustoken);
}

void FileManager::CreateParticleJSON(const char* pass, ParitcleSetting* setting) {

	std::string filename = pass;
	std::ofstream file;

	file.open(filename);
	assert(file);

	if (file.is_open()) {
		
		json data;
		data["Amount"] = setting->Amount;
		data["RandomSpeed"] = setting->RandomSpeed;
		data["PolarCoordinates"] = setting->PolarCoordinates; 

		data["Position"]["x"] = setting->Position.x;
		data["Position"]["y"] = setting->Position.y;
		data["Position"]["z"] = setting->Position.z;

		data["PostionMinMaxX"]["x"] = setting->PostionMinMaxX.x;
		data["PostionMinMaxX"]["y"] = setting->PostionMinMaxX.y;
		data["PostionMinMaxY"]["x"] = setting->PostionMinMaxY.x;
		data["PostionMinMaxY"]["y"] = setting->PostionMinMaxY.y;
		data["PostionMinMaxZ"]["x"] = setting->PostionMinMaxZ.x;
		data["PostionMinMaxZ"]["y"] = setting->PostionMinMaxZ.y;

		data["Speed"]["x"] = setting->Speed.x;
		data["Speed"]["y"] = setting->Speed.y;
		data["Speed"]["z"] = setting->Speed.z;

		data["SpeedMinMaxX"]["x"] = setting->SpeedMinMaxX.x;
		data["SpeedMinMaxX"]["y"] = setting->SpeedMinMaxX.y;
		data["SpeedMinMaxY"]["x"] = setting->SpeedMinMaxY.x;
		data["SpeedMinMaxY"]["y"] = setting->SpeedMinMaxY.y;
		data["SpeedMinMaxZ"]["x"] = setting->SpeedMinMaxZ.x;
		data["SpeedMinMaxZ"]["y"] = setting->SpeedMinMaxZ.y;

		data["LifeMinMax"]["x"] = setting->LifeMinMax.x;
		data["LifeMinMax"]["y"] = setting->LifeMinMax.y;

		data["Size"] = setting->Size;

		file << data << std::endl;
		file.close();

		MessageBox(GetWindow(), "セーブ成功", "パーティクルデータ", MB_ICONINFORMATION);

	}
}

ParitcleSetting FileManager::ReadParticleJSON(const char* pass) {

	std::string filename = pass;
	std::ifstream file;
	ParitcleSetting setting;

	file.open(filename);

	if (file.is_open()) {

		json data;
		file >> data;

		setting.Amount = data["Amount"];
		setting.RandomSpeed = data["RandomSpeed"];
		setting.PolarCoordinates = data["PolarCoordinates"];

		setting.Position.x = data["Position"]["x"];
		setting.Position.y = data["Position"]["y"];
		setting.Position.z = data["Position"]["z"];

		setting.PostionMinMaxX.x = data["PostionMinMaxX"]["x"];
		setting.PostionMinMaxX.y = data["PostionMinMaxX"]["y"];
		setting.PostionMinMaxY.x = data["PostionMinMaxY"]["x"];
		setting.PostionMinMaxY.y = data["PostionMinMaxY"]["y"];
		setting.PostionMinMaxZ.x = data["PostionMinMaxZ"]["x"];
		setting.PostionMinMaxZ.y = data["PostionMinMaxZ"]["y"];

		setting.Speed.x = data["Speed"]["x"];
		setting.Speed.y = data["Speed"]["y"];
		setting.Speed.z = data["Speed"]["z"];

		setting.SpeedMinMaxX.x = data["SpeedMinMaxX"]["x"];
		setting.SpeedMinMaxX.y = data["SpeedMinMaxX"]["y"];
		setting.SpeedMinMaxY.x = data["SpeedMinMaxY"]["x"];
		setting.SpeedMinMaxY.y = data["SpeedMinMaxY"]["y"];
		setting.SpeedMinMaxZ.x = data["SpeedMinMaxZ"]["x"];
		setting.SpeedMinMaxZ.y = data["SpeedMinMaxZ"]["y"];

		setting.LifeMinMax.x = data["LifeMinMax"]["x"];
		setting.LifeMinMax.y = data["LifeMinMax"]["y"];

		setting.Size = data["Size"];
	}

	file.close();
	return setting;
}