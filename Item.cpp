#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Item.h"
#include "input.h"
#include "Shader.h"
#include "ModelManager.h"

void Item::Init() {
	
	Name = "Item";

	Position = D3DXVECTOR3(0, 0.0f, 0);
	Rotation = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&this->Quaternion);

	mModel = AddComponent<ModelManager>();
	mModel->SetModel(Application::GetScene()->GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::SWORD));

	Resource::Init();
}

void Item::Uninit() {
	Resource::Uninit();
}

void Item::Update() {


	ImGui::Begin(Name.c_str());
	ImGui::SliderFloat3(u8"座標", Position, -1000.0f, 1000.0f, "%.0f", 5.0f);
	ImGui::SliderFloat3(u8"回転", Rotation, -3.14f, 3.14f);
	ImGui::SliderFloat3(u8"スケール", Scale, 0.1f, 10.0f);
	ImGui::End();

	Resource::Update();
}

void Item::Render() {

	D3DXMATRIX world = MakeWorldMatrix();
	Renderer::SetWorldMatrix(&world);

	Shader::Use(SHADER_TYPE_VSPS::Default);

	mModel->Render(world);

}