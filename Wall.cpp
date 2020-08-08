#include "main.h"
#include "Renderer.h"
#include "Wall.h"
#include "Application.h"
#include "Scene.h"

void Wall::Init() {

	Name = "Wall";

	m_Model = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::CUBE);

	Position = D3DXVECTOR3(0, 0, 0);
	Rotation = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(10.0f, 1.0f, 1.0f);

	m_Model->DisplayConfig = false;

	AddComponent<BoxCollider>();
	
	Resource::Init();
}

void Wall::Uninit() {

	Resource::Uninit();
}

void Wall::Update() {

	
	GetComponent<BoxCollider>()->Update(Position, Rotation, Scale);
}

void Wall::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw(world);
	GetComponent<BoxCollider>()->Render();
}

