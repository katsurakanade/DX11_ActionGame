#include "main.h"
#include "Scene.h"
#include "Application.h"
#include "Renderer.h"
#include "Particle.h"
#include "ParticleManager.h"

void ParticleManager::Init() {
	
}

void ParticleManager::Uninit() {

}

void ParticleManager::Update() {

	Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
	Position = p->Position;

	ImGui::Begin(u8"パーティクルマネージャー");
	ImGui::SliderInt("Amount", &mSetting.Amount, 1, 100000);
	ImGui::SliderFloat2("PostionMinMaxX", mSetting.PostionMinMaxX, -100.0f, 100.0f);
	ImGui::SliderFloat2("PostionMinMaxY", mSetting.PostionMinMaxY, -100.0f, 100.0f);
	ImGui::SliderFloat2("PostionMinMaxZ", mSetting.PostionMinMaxZ, -100.0f, 100.0f);
	ImGui::SliderFloat2("SpeedMinMaxX", mSetting.SpeedMinMaxX, -50.0f, 50.0f);
	ImGui::SliderFloat2("SpeedMinMaxY", mSetting.SpeedMinMaxY, -50.0f, 50.0f);
	ImGui::SliderFloat2("SpeedMinMaxZ", mSetting.SpeedMinMaxZ, -50.0f, 50.0f);
	ImGui::SliderFloat2("LifeMinMax", mSetting.LifeMinMax, 1.0f, 5000.0f);
	ImGui::SliderFloat("Size", &mSetting.Size, 0.05f, 2.0f);
	ImGui::Checkbox("RandomSpeed", &mSetting.RandomSpeed);
	ImGui::Checkbox("PolarCoordinates", &mSetting.PolarCoordinates);

	if (ImGui::Button(u8"生成")) {
		ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
		pc->Create(&mSetting);
		pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
		pc->Position = Position;
	}

	ImGui::End();
}

