#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "BackGround.h"

void BackGround::Init() {

	Name = "ClassRoom";

	//m_Model = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::CLASSROOM);

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(0.15f, 0.1f, 0.1f);

	m_Model->DisplayConfig = true;
	m_Model->SetConfingPos(D3DXVECTOR2(100, 100));
}

void BackGround::Uninit() {

}

void BackGround::Update() {

}

void BackGround::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw(world);
}