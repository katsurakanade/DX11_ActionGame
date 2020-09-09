#include "main.h"
#include "input.h"
#include "Result.h"
#include "Application.h"
#include "StaticManger.h"

void Result::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);
	AddGameObject<Skybox>(ObjectLayer);

	Sprite* logo = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	logo->Name = "Logo";
	if (StaticManger::StateMap["GameClear"] == "true") {
		logo->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::CLEAR));
	}
	else if (StaticManger::StateMap["GameClear"] == "false") {
		logo->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::GAMEOVER));
	}
	logo->SetSize(D3DXVECTOR3(1280, 400, 0));
	logo->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 550, SCREEN_HEIGHT / 2 - 550));

	//Sprite* Button = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	//Button->Name = "Button";
	//Button->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::SPACEBUTTON));
	//Button->SetSize(D3DXVECTOR3(400, 120, 0));
	//Button->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT - 200));

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;

	AudioListener::Play(Application::GetAsset()->GetSound((int)SOUND_ENUM::BGM_03), -1,0.1f);
}

void Result::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				AudioListener::Stop(Application::GetAsset()->GetSound((int)SOUND_ENUM::BGM_03));
				Application::SwitchScene<Title>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (Input::GetKeyTrigger(VK_SPACE) && !mClear) {
		AudioListener::Play(Application::GetAsset()->GetSound((int)SOUND_ENUM::SE_01), 0,0.5f);
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}

}