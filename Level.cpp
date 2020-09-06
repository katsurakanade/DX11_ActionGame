#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Wall.h"
#include "Enemy.h"
#include "Level.h"
#include <random>

void Level::Init() {

	Name = "Level";

	Wall* ground = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	ground->Name = "Ground";
	ground->Position = D3DXVECTOR3(0, 0, 30);
	ground->Rotation = D3DXVECTOR3(0, 0, 0);
	ground->Scale = D3DXVECTOR3(100, 1, 40);
	ground->SetFront(D3DXVECTOR3(0, -1, 0));
	ground->ResetPositionOffest();

	/*Wall* base = Application::GetScene()->AddGameObject<Wall>(ObjectLayer);
	base->Name = "Base_1";
	base->Position = D3DXVECTOR3(-20, 20, 30);
	base->Rotation = D3DXVECTOR3(0, 0, 0);
	base->Scale = D3DXVECTOR3(20, 1, 40);
	base->SetFront(D3DXVECTOR3(0, 1, 0));
	base->ResetPositionOffest();*/

}
