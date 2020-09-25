#include "main.h"
#include "input.h"
#include "Game.h"
#include "Application.h"
#include "Debug.h"
#include "Particle.h"
#include "Item.h"
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
	//Enemy* enemy = AddGameObject<Enemy>(ObjectLayer);
	//enemy->AddGauge();

	MeshField* mf = AddGameObject<MeshField>(ObjectLayer);

	Item* t = AddGameObject<Item>(ObjectLayer);
	t->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::SWORD));
	t->Position = D3DXVECTOR3(10, 18, -50);
	t->Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	Gamemanger* manger = AddGameObject<Gamemanger>(ObjectLayer);

	for (int i = 0; i < 10; i++) {
		Effect* plant = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
		plant->Name = "Plant";
		plant->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PLANT));
		plant->SetHW(1, 1);
		plant->SetLoop(true);
		plant->Position = D3DXVECTOR3(-30 +(i *5), 14, 0);
		plant->Scale = D3DXVECTOR3(5.0f, 4.0f, 4.0f);
	}


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
