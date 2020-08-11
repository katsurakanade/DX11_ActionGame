#include "main.h"
#include "Renderer.h"
#include "Wall.h"
#include "Application.h"
#include "Scene.h"

void Wall::Init() {

	Name = "Wall";

	mModel = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::CUBE);

	Position = D3DXVECTOR3(0, 0, 0);
	Rotation = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(50.0f, 50.0f, 10.0f);

	AddComponent<BoxCollider>()->mPositionOffest.y = Scale.y /2;
	
	Resource::Init();
}

void Wall::Uninit() {

	Resource::Uninit();
}

void Wall::Update() {

	/*{
		ImGui::Begin(u8"•Ç");
		ImGui::SliderFloat3(u8"‰ñ“]", Rotation, -3.14f, 3.14f);
		ImGui::End();
	}*/

	Resource::Update();
}

void Wall::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mModel->Draw(world);

	GetComponent<BoxCollider>()->Render();
}

