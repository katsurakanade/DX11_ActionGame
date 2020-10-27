#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"
#include "Particle.h"
#include "Item.h"
#include "MeshField.h"
#include "Grass.h"


void Game::Init() {

	mAsset = new Asset(SCENE_ASSET::GAME);
	mAsset->LoadSceneAsset();
	Application::SetAsset(mAsset);

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(ObjectLayer);
	skybox->SetModelTexture(2);

	Player* player = AddGameObject<Player>(ObjectLayer);

	Enemy* enemy = AddGameObject<Enemy>(ObjectLayer);
	enemy->AddGauge();
	enemy->Position = D3DXVECTOR3(0, 0, -150);

	Enemy* enemy2 = AddGameObject<Enemy>(ObjectLayer);
	enemy2->AddGauge();
	enemy2->Position = D3DXVECTOR3(-50, 0, -150);

	Enemy* enemy3 = AddGameObject<Enemy>(ObjectLayer);
	enemy3->AddGauge();
	enemy3->Position = D3DXVECTOR3(10, 0, -200);

	Item* item = AddGameObject<Item>(ObjectLayer);
	item->Position = D3DXVECTOR3(10, 43, 2);

	MeshField* mf = AddGameObject<MeshField>(ObjectLayer);

	GUI* gui = AddGameObject<GUI>(SpriteLayer);

	//Fade* fade = AddGameObject<Fade>(FadeLayer);
	//fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	//mpFade = fade;


	AudioListener::Play(Application::GetAsset()->GetSound((int)SOUND_ENUM_GAME::BGM_02), -1, 0.05f);

}

void Game::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				AudioListener::Stop(Application::GetAsset()->GetSound((int)SOUND_ENUM_GAME::BGM_02));
				Application::SwitchScene<Result>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (mSwitchFlag && !mClear) {
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade; 
		mClear = true;
	}

	if (Input::GetKeyTrigger(DIK_T)) {
		AudioListener::Stop(Application::GetAsset()->GetSound((int)SOUND_ENUM_GAME::BGM_02));
		Application::SwitchScene<Title>();
	}
}
