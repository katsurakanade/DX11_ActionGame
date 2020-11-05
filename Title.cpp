#include "main.h"
#include "input.h"
#include "Title.h"
#include "Application.h"
#include "Particle.h"

void Title::Init() {

	mAsset = new Asset(SCENE_ASSET::TITLE);
	mAsset->LoadSceneAsset();
	Application::SetAsset(mAsset);

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

	Skybox* skybox = Application::GetScene()->AddGameObject<Skybox>(ObjectLayer);
	skybox->SetModelTexture(1);

	Sprite* title_icon = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	title_icon->Name = "title_icon";
	title_icon->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_TITLE::TITLE));
	title_icon->Position = D3DXVECTOR3(437, 62, 1);
	title_icon->GetImage()->Set2DSize(D3DXVECTOR3(1000, 175, 1));

	Sprite* spacebutton = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	spacebutton->Name = "spacebutton";
	spacebutton->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_TITLE::SPACEBUTTON));
	spacebutton->Position = D3DXVECTOR3(671, 780, 1);
	spacebutton->GetImage()->Set2DSize(D3DXVECTOR3(500, 175, 1));

	Fade* fade = AddGameObject<Fade>(FadeLayer);
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
		fade->Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}

	if (!mStart) {

		ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
		ParitcleSetting* setting = new ParitcleSetting;
		setting->Amount = 150000;
		setting->PostionMinMaxX = D3DXVECTOR2(-100, 100);
		setting->PostionMinMaxY = D3DXVECTOR2(-100, 100);
		setting->PostionMinMaxZ = D3DXVECTOR2(-100, 100);
		setting->SpeedMinMaxX = D3DXVECTOR2(0.0f, 0.0f);
		setting->SpeedMinMaxY = D3DXVECTOR2(0.01f, 0.02f);
		setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 0.0f);
		setting->LifeMinMax = D3DXVECTOR2(300000.0f, 300000.0f);
		setting->Size = 0.1f;
		pc->Create(setting);
		pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_TITLE::PARTICLE));
		delete setting;

		Application::GetScene()->GetGameObject<Camera>(CameraLayer)->SetFollowTarget(pc);

		mStart = true;
	}

}
