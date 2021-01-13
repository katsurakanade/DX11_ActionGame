#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"
#include "Particle.h"
#include "Item.h"
#include "MeshField.h"
#include "Grass.h"
#include "LevelTools.h"
#include "ParticleManager.h"

void Game::Init() {

	Asset::GetInstance()->SetScene(SCENE_ASSET::GAME);
	Asset::GetInstance()->LoadSceneAsset();

	mMaincamera = AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(ObjectLayer);
	skybox->SetModelTexture(2);

	Player* player = AddGameObject<Player>(ObjectLayer);
	player->Position = D3DXVECTOR3(75, 0, -100);

	Enemy* enemy = AddGameObject<Enemy>(ObjectLayer);
	enemy->Name = "Boss";
	enemy->Position = player->Position + D3DXVECTOR3(0, 0, -80);
	enemy->Create();

	//Enemy* enemy_2 = AddGameObject<Enemy>(ObjectLayer);
	//enemy_2->Name = "Enemy_2";
	//enemy_2->Position = player->Position + D3DXVECTOR3(0, 0, -80);
	//enemy_2->Create();

	//Enemy* enemy_1 = AddGameObject<Enemy>(ObjectLayer);
	//enemy_1->Name = "Enemy_2";
	//enemy_1->Position = player->Position + D3DXVECTOR3(-30, 0, -80);
	//enemy_1->Create();

	MeshField* mf = AddGameObject<MeshField>(ObjectLayer);
	LevelTools* lt = AddGameObject<LevelTools>(ObjectLayer);
	ParticleManager* pm = AddGameObject<ParticleManager>(ObjectLayer);

	GUI* gui = AddGameObject<GUI>(SpriteLayer);

	AudioListener::Play(Asset::GetInstance()->GetSound((int)SOUND_ENUM_GAME::BGM_02), -1, 0.05f);

}

void Game::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				AudioListener::Stop(Asset::GetInstance()->GetSound((int)SOUND_ENUM_GAME::BGM_02));
				Application::SwitchScene<Title>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (Input::GetKeyTrigger(DIK_T) && !mClear) {

		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}

}
