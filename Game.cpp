#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"

void Game::Init() {

	mAsset = new Asset(SCENE_ASSET::GAME);
	mAsset->LoadSceneAsset();
	Application::SetAsset(mAsset);

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(SpriteLayer);
	skybox->SetModelTexture(1);

	Level* level = AddGameObject<Level>(ObjectLayer);

	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			Player* player = AddGameObject<Player>(ObjectLayer);
			player->Position = D3DXVECTOR3(10 * i, 12, 10 * k);
		}
	}

	//Player* player = AddGameObject<Player>(ObjectLayer);
	Gamemanger* manger = AddGameObject<Gamemanger>(ObjectLayer);
	/*GUI* gui = AddGameObject<GUI>(SpriteLayer);*/

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;

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
