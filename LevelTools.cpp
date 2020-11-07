#include "main.h"
#include "renderer.h"
#include "LevelTools.h"
#include "Application.h"
#include "Shader.h"
#include "FileManger.h"
#include "ModelManager.h"
#include "Grass.h"
#include "Props.h"
#include <random>

void LevelTools::Init() {
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
}

void LevelTools::Uninit() {

}

void LevelTools::Update() {

	ImGui::Begin(u8"レベルデザインツール", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::PushItemWidth(30);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu(u8"マップオブジェク"))
		{
			if (ImGui::MenuItem(u8"Save")) {
				std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
				FileManger::WriteResource("grass.json", grasslist);
				std::vector<Props*> propslist = Application::GetScene()->GetGameObjects<Props>(ObjectLayer);
				FileManger::WriteResource("rock.json", propslist);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	if (ImGui::TreeNode(u8"マップオブジェクト追加")) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f });
		if (ImGui::Button(u8"岩")) {
			Props* rock = Application::GetScene()->AddGameObject<Props>(ObjectLayer);
			rock->GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));
			rock->Name = "Rock_" + std::to_string(Application::RandomDevice());
			rock->Tag = "Rock";
			rock->Type = "Object";
			rock->Position = mpPlayer->Position;
			rock->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		}
		if (ImGui::Button(u8"壁")) {
			Props* rock = Application::GetScene()->AddGameObject<Props>(ObjectLayer);
			rock->GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::WALL));
			rock->Name = "Wall_" + std::to_string(Application::RandomDevice());
			rock->Tag = "Wall";
			rock->Type = "Object";
			rock->Position = mpPlayer->Position;
			rock->Scale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		}
		ImGui::PopStyleColor();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"マップオブジェクトリスト")) {
		std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
		std::vector<Props*> propslist = Application::GetScene()->GetGameObjects<Props>(ObjectLayer);
		for (unsigned int i = 0; i < grasslist.size(); i++) {
			if (ImGui::TreeNode(grasslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"座標", grasslist[i]->Position, -200.0f, 200.0f, "%.1f", 1.0f);
				ImGui::SliderFloat3(u8"回転", grasslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"スケール", grasslist[i]->Scale, 0.1f, 10.0f);
				if (ImGui::Button(u8"削除")) {
					grasslist[i]->Destroy();
				}
				ImGui::TreePop();
			}
		}
		for (unsigned int i = 0; i < propslist.size(); i++) {
			if (ImGui::TreeNode(propslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"座標", propslist[i]->Position, -200.0f, 200.0f, "%.1f", 1.0f);
				ImGui::SliderFloat3(u8"回転", propslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"スケール", propslist[i]->Scale, 0.1f, 100.0f);
				if (ImGui::Button(u8"削除")) {
					propslist[i]->Destroy();
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

void LevelTools::Render() {

}