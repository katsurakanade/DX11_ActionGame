#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Arrow.h"

void Arrow::Init() {

	Name = "Arrow";

	//mModel = Application::GetAsset()->GetAssimpModel(ASSIMP_MODEL_ENUM::TORUS);

	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&Quaternion);

	Resource::Init();
}

void Arrow::Uninit() {
	Resource::Uninit();
}

void Arrow::Update() {
	Resource::Update();
}

void Arrow::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mModel->Draw(world);
}