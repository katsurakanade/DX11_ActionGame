#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"
#include "Particle.h"
#include "Torus.h"
#include "MeshField.h"

void Game::Init() {

	mAsset = new Asset(SCENE_ASSET::GAME);
	mAsset->LoadSceneAsset();
	Application::SetAsset(mAsset);

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(SpriteLayer);
	skybox->SetModelTexture(1);

	/*Level* level = AddGameObject<Level>(ObjectLayer);*/

	Player* player = AddGameObject<Player>(ObjectLayer);
	Enemy* enemy = AddGameObject<Enemy>(ObjectLayer);
	enemy->AddGauge();

	MeshField* mf = AddGameObject<MeshField>(ObjectLayer);

	//Torus* t = AddGameObject<Torus>(ObjectLayer);
	//t->Simple = true;
	//t->Position = D3DXVECTOR3(10, 12, 0);

	//Torus* t2 = AddGameObject<Torus>(ObjectLayer);
	//t2->Simple = false;
	//t2->Position = D3DXVECTOR3(0, 12, 0);

	Gamemanger* manger = AddGameObject<Gamemanger>(ObjectLayer);

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;

	//AudioListener::Play(Application::GetAsset()->GetSound((int)SOUND_ENUM_GAME::BGM_02), -1, 0.05f);

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
