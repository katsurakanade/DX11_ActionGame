#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"

void Game::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	AddGameObject<Skybox>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);

	Level* level = AddGameObject<Level>(ObjectLayer);
	Player* player = AddGameObject<Player>(ObjectLayer);
	Gamemanger* manger = AddGameObject<Gamemanger>(ObjectLayer);
	GUI* gui = AddGameObject<GUI>(SpriteLayer);

}

void Game::Update() {

	Scene::Update();

	if (mSwitchFlag) {
		Application::SwitchScene<Title>();
	}
}
