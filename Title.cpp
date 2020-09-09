#include "main.h"
#include "input.h"
#include "Title.h"
#include "Application.h"

void Title::Init() {

	mAsset = new Asset(SCENE_ASSET::TITLE);
	mAsset->LoadSceneAsset();
	Application::SetAsset(mAsset);

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(SpriteLayer);
	skybox->SetModelTexture(1);

	Sprite* logo = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	logo->Name = "TitleLogo";
	logo->SetTexture(mAsset->GetTexture((int)TEXTURE_ENUM_TITLE::LOGO));
	logo->SetSize(D3DXVECTOR3(1000, 500, 0));
	logo->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 - 550));

	Sprite* Button = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	Button->Name = "Button";
	Button->SetTexture(mAsset->GetTexture((int)TEXTURE_ENUM_TITLE::SPACEBUTTON));
	Button->SetSize(D3DXVECTOR3(400, 120, 0));
	Button->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT  - 200));

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;

	AudioListener::Play(mAsset->GetSound((int)SOUND_ENUM_TITLE::BGM_01), -1,0.1f);
}

void Title::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				AudioListener::Stop(mAsset->GetSound((int)SOUND_ENUM_TITLE::BGM_01));
				Application::SwitchScene<Game>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (Input::GetKeyTrigger(DIK_SPACE) && !mClear) {
		
		AudioListener::Play(mAsset->GetSound((int)SOUND_ENUM_TITLE::SE_01), 0,0.5f);
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}

}
