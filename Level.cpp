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
	ground->Position = D3DXVECTOR3(0, 0, 0);
	ground->Rotation = D3DXVECTOR3(0, 0, 0);
	ground->Scale = D3DXVECTOR3(300, 1, 300);
	ground->SetFront(D3DXVECTOR3(0, -1, 0));
	ground->ResetPositionOffest();


}
