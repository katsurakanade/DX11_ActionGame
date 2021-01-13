#include "main.h"
#include "input.h"
#include "Title.h"
#include "Application.h"
#include "Particle.h"

void Title::Init() {

	Asset::GetInstance()->SetScene(SCENE_ASSET::TITLE);
	Asset::GetInstance()->LoadSceneAsset();

	mMaincamera =  AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);


	mSkybox = Application::GetScene()->AddGameObject<Skybox>(ObjectLayer);
	mSkybox->Rotation = D3DXVECTOR3(0, 1.5f, 0);
	mSkybox->SetModelTexture(1);

	mTitleIcon = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	mTitleIcon->Name = "title_icon";
	mTitleIcon->GetImage()->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_TITLE::TITLE));
	mTitleIcon->Position = D3DXVECTOR3(437, 62, 1);
	mTitleIcon->GetImage()->Set2DSize(D3DXVECTOR3(1000, 175, 1));

	mButtonIcon = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	mButtonIcon->Name = "spacebutton";
	mButtonIcon->GetImage()->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_TITLE::SPACEBUTTON));
	mButtonIcon->Position = D3DXVECTOR3(671, 780, 1);
	mButtonIcon->GetImage()->Set2DSize(D3DXVECTOR3(500, 175, 1));


	AudioListener::Play(Asset::GetInstance()->GetSound((int)SOUND_ENUM_TITLE::BGM_01), -1,0.1f);
}

void Title::Update() {

	Scene::Update();

	if (GetGameObject<ParticleSystem>(EffectLayer) == nullptr)
		CreateTitle();

	if (mpFade != nullptr) {
		if (!mpFade->GetIsFade()) {
			if (mClear) {
				AudioListener::Stop(Asset::GetInstance()->GetSound((int)SOUND_ENUM_TITLE::BGM_01));
				Application::SwitchScene<Game>();
				return;
			}
			mpFade->Destroy();
		}
	}

	if (Input::GetKeyTrigger(DIK_SPACE) && !mClear) {

		AudioListener::Play(Asset::GetInstance()->GetSound((int)SOUND_ENUM_TITLE::SE_01), 0, 0.5f);
		Fade* fade = AddGameObject<Fade>(FadeLayer);
		fade->Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		mpFade = fade;
		mClear = true;
	}
	
}

void Title::CreateTitle() {

	mParticle = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
	mParticle->Create(&FileManager::ReadParticleJSON("asset\\json_particle\\Title_Particle.json"));
	mParticle->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_TITLE::PARTICLE));
	Application::GetScene()->GetGameObject<Camera>(CameraLayer)->SetFollowTarget(mParticle);

}
