#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Wall.h"
#include "Enemy.h"
#include "Level.h"

void Level::Init() {

	Wall* ground = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	ground->Position = D3DXVECTOR3(0, 0, 20);
	ground->Rotation = D3DXVECTOR3(0, 0, 0);
	ground->Scale = D3DXVECTOR3(150, 1, 80);
	ground->SetFront(D3DXVECTOR3(0, 1, 0));
	ground->ResetPositionOffest();

	Wall* right = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	right->Position = D3DXVECTOR3(75, 0, 20);
	right->Rotation = D3DXVECTOR3(0, 0, 0);
	right->Scale = D3DXVECTOR3(1, 20, 80);
	right->SetFront(D3DXVECTOR3(-1, 0, 0));
	right->ResetPositionOffest();

	Wall* left = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	left->Position = D3DXVECTOR3(-75, 0, 20);
	left->Rotation = D3DXVECTOR3(0, 0, 0);
	left->Scale = D3DXVECTOR3(1, 20, 80);
	left->SetFront(D3DXVECTOR3(1, 0, 0));
	left->ResetPositionOffest();

	Wall* Back = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	Back->Position = D3DXVECTOR3(0, 0, 60);
	Back->Rotation = D3DXVECTOR3(0, 0, 0);
	Back->Scale = D3DXVECTOR3(150, 20, 1);
	Back->SetFront(D3DXVECTOR3(0, 0, -1));
	Back->ResetPositionOffest();

	Wall* Front = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	Front->Position = D3DXVECTOR3(0, 0, -20);
	Front->Rotation = D3DXVECTOR3(0, 0, 0);
	Front->Scale = D3DXVECTOR3(150, 20, 1);
	Front->SetFront(D3DXVECTOR3(0, 0, 1));
	Front->ResetPositionOffest();

	Enemy* e1 = Application::GetScene()->AddGameObject<Enemy>(ObjectLayer);
	e1->Position = D3DXVECTOR3(0, 10, 0);
	
}
