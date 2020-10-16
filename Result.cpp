#include "main.h"
#include "input.h"
#include "Result.h"
#include "Application.h"
#include "StaticManger.h"

void Result::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);
	AddGameObject<Skybox>(ObjectLayer);

	Fade* fade = AddGameObject<Fade>(FadeLayer);
	fade->Start(false, 90, D3DCOLOR_RGBA(1, 1, 1, 1));
	mpFade = fade;

	
}

void Result::Update() {

	Scene::Update();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				//AudioListener::Stop(Application::GetAsset()->GetSound((int)SOUND_ENUM::BGM_03));
				Application::SwitchScene<Title>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (Input::GetKeyTrigger(VK_SPACE) && !mClear) {
		//AudioListener::Play(Application::GetAsset()->GetSound((int)SOUND_ENUM::SE_01), 0,0.5f);
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}

}