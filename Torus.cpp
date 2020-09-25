#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Torus.h"
#include "input.h"
#include "Shader.h"

void Torus::Init() {

	Name = "Torus";

	mModel = Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::SWORD);

	Position = D3DXVECTOR3(0, 20.0f, 0);
	Rotation = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	D3DXQuaternionIdentity(&this->Quaternion);

	//Camera* camera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);
	//camera->SetFollowTarget(this);

	Resource::Init();

}

void Torus::Uninit() {
	mCmodel->Unload();
	delete mCmodel;
	Resource::Uninit();
}

void Torus::Update() {

	if (Input::GetKeyPress('A'))
		Position.x -= 0.1f;

	if (Input::GetKeyPress('D'))
		Position.x += 0.1f;

	if (Input::GetKeyPress('W'))
		Position.z += 0.1f;

	if (Input::GetKeyPress('S'))
		Position.z -= 0.1f;


	if (Input::GetKeyPress(DIK_R))
		Rotation.x -= 5.0f * Time::GetDeltaTime();
	if (Input::GetKeyPress(DIK_F))
		Rotation.x += 5.0f * Time::GetDeltaTime();

	if (Input::GetKeyPress(DIK_Q))
		Rotation.y -= 5.0f * Time::GetDeltaTime();
	if (Input::GetKeyPress(DIK_E))
		Rotation.y += 5.0f * Time::GetDeltaTime();


	Resource::Update();

	ImGui::Begin(Name.c_str());
	ImGui::SliderFloat3(u8"座標", Position, -1000.0f, 1000.0f, "%.0f", 5.0f);
	ImGui::SliderFloat3(u8"回転", Rotation, -3.14f, 3.14f);
	ImGui::SliderFloat3(u8"スケール", Scale, 0.1f, 10.0f);
	ImGui::End();
}

void Torus::Render() {


	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	Shader::Use(SHADER_TYPE_VSPS::Default);

	mModel->Draw(world);

}