#include "main.h"
#include "input.h"
#include "Title.h"
#include "Application.h"

void Title::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);
	AddGameObject<Skybox>(ObjectLayer);
	
	Sprite* logo = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	logo->Name = "TitleLogo";
	logo->SetTexture(Asset::GetTexture(TEXTURE_ENUM::LOGO));
	logo->SetSize(D3DXVECTOR3(1000, 500, 0));
	logo->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 - 550));
}

void Title::Update() {

	Scene::Update();

	if (Input::GetKeyTrigger(VK_SPACE)) {
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(true , 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
	}

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			mpFade->Destroy();
			Application::SwitchScene<Game>();
		}
	}

}
