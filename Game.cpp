#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"
#include "Particle.h"
#include "Item.h"
#include "MeshField.h"
#include "field.h"
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
	//enemy->AddGauge();
	enemy->Position = D3DXVECTOR3(0, 0, -150);

	//Item* item = AddGameObject<Item>(ObjectLayer);
	//item->SetModel(mAsset->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::CUBE));
	//item->Position = D3DXVECTOR3(0, 0, -50);

	/*ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
	pc->Position = D3DXVECTOR3(0, 250, 0);
	pc->Create(-1000, 1000, -0.1f, 0.1f, 0.5f);*/

	MeshField* mf = AddGameObject<MeshField>(ObjectLayer);

	GUI* gui = AddGameObject<GUI>(SpriteLayer);

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
