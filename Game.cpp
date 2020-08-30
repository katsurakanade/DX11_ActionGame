#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"

void Game::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	AddGameObject<Skybox>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);

	Level* level = AddGameObject<Level>(ObjectLayer);
	level->SetRound(0);
	Player* player = AddGameObject<Player>(ObjectLayer);
	Gamemanger* manger = AddGameObject<Gamemanger>(ObjectLayer);
	GUI* gui = AddGameObject<GUI>(SpriteLayer);

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;

	AudioListener::Play(Asset::GetSound(SOUND_ENUM::BGM_02), -1);

}

void Game::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				AudioListener::Stop(Asset::GetSound(SOUND_ENUM::BGM_02));
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

}
