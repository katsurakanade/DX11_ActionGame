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

	ImGui::Begin(u8"���x���f�U�C���c�[��", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::PushItemWidth(30);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu(u8"�}�b�v�I�u�W�F�N"))
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
	if (ImGui::TreeNode(u8"�}�b�v�I�u�W�F�N�g�ǉ�")) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f });
		if (ImGui::Button(u8"��")) {
			Props* rock = Application::GetScene()->AddGameObject<Props>(ObjectLayer);
			rock->GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));
			rock->Name = "Rock_" + std::to_string(Application::RandomDevice());
			rock->Tag = "Rock";
			rock->Type = "Object";
			rock->Position = mpPlayer->Position;
			rock->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		}
		if (ImGui::Button(u8"��")) {
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
	if (ImGui::TreeNode(u8"�}�b�v�I�u�W�F�N�g���X�g")) {
		std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
		std::vector<Props*> propslist = Application::GetScene()->GetGameObjects<Props>(ObjectLayer);
		for (unsigned int i = 0; i < grasslist.size(); i++) {
			if (ImGui::TreeNode(grasslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"���W", grasslist[i]->Position, -200.0f, 200.0f, "%.1f", 1.0f);
				ImGui::SliderFloat3(u8"��]", grasslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"�X�P�[��", grasslist[i]->Scale, 0.1f, 10.0f);
				if (ImGui::Button(u8"�폜")) {
					grasslist[i]->Destroy();
				}
				ImGui::TreePop();
			}
		}
		for (unsigned int i = 0; i < propslist.size(); i++) {
			if (ImGui::TreeNode(propslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"���W", propslist[i]->Position, -200.0f, 200.0f, "%.1f", 1.0f);
				ImGui::SliderFloat3(u8"��]", propslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"�X�P�[��", propslist[i]->Scale, 0.1f, 100.0f);
				if (ImGui::Button(u8"�폜")) {
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