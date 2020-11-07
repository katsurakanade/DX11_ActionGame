#include "main.h"
#include "FileManger.h"
#include "Application.h"
#include "Scene.h"
#include "Props.h"
#include "ModelManager.h"
#include "Lib/nlohmann/json.hpp"
using namespace std;
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>

using json = nlohmann::json;

// マップロード
void FileManger::Read(const char* pass,float output[FIELD_X][FIELD_X]) {

	std::string filename = pass;
	std::ifstream file;

	file.open(filename);

	// Fill
	if (file.is_open()) {
		for (int i = 0; i < FIELD_X; i++) {
			for (int k = 0; k < FIELD_X; k++) {
				file >> output[i][k];
			}
		}

		file.close();
	}


}

void FileManger::Write(const char* pass, float output[FIELD_X][FIELD_X]) {

	std::string filename = pass;
	std::ofstream file;

	file.open(filename);
	assert(file);

	// Fill
	if (file.is_open()) {
		for (int i = 0; i < FIELD_X; i++) {
			for (int k = 0; k < FIELD_X; k++) {
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
					g->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PLANT));
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
						p->GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));
					}
				}

				else if (data["Tag"] == "Wall") {
					if (p->GetComponent<ModelManager>()) {
						p->GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::WALL));
					}
				}
			}
		

		}

		file.close();
	}
}

void FileManger::ReadImageMap(const char* pass, float output[FIELD_X][FIELD_X]) {

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

