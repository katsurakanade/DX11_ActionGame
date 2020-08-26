#include "main.h"
#include "input.h"
#include "Title.h"
#include "Application.h"

void Title::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(SpriteLayer);
	skybox->SetModelTexture(5);

	Sprite* logo = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	logo->Name = "TitleLogo";
	logo->SetTexture(Asset::GetTexture(TEXTURE_ENUM::LOGO));
	logo->SetSize(D3DXVECTOR3(1000, 500, 0));
	logo->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 - 550));

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;
}

void Title::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				Application::SwitchScene<Game>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (Input::GetKeyTrigger(VK_SPACE) && !mClear) {
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}

}
