#include "main.h"
#include "Light.h"

void Light::Init() {

	Name = "Light";

	mSource = new LIGHT();

	mSource->Direction = D3DXVECTOR4(0.0f, 1.0f, -0.1f, 0.0f);
	D3DXVec4Normalize(&mSource->Direction, &mSource->Direction);
	mSource->Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	mSource->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mSource->Enable = true;

}

void Light::Uninit() {

	if (mSource) {
		delete mSource;
		mSource = nullptr;
	}
}

void Light::Update() {

	ImGui::Begin(u8"ƒ‰ƒCƒg");
	ImGui::SliderFloat4("Direction", mSource->Direction, -1.0f, 1.0f);
	ImGui::SliderFloat4("Ambient", mSource->Ambient, 0.0f, 1.0f);
	ImGui::SliderFloat4("Diffuse", mSource->Diffuse, 0.0f, 1.0f);
	ImGui::End();

}

void Light::Render() {

	Renderer::SetLight(*mSource);

}


