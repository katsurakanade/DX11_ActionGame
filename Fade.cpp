#include "main.h"
#include "Application.h"
#include "Scene.h"
#include "Fade.h"

void Fade::Init() {

	mIsFade = false;
	mAlpha = 0.0f;

	Sprite* sp = Application::GetScene()->AddGameObject<Sprite>(FadeLayer);
	sp->Name = "FadeSprite";
	if (Application::GetAsset()->GetScene() == SCENE_ASSET::TITLE) {
		sp->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_TITLE::WHITE));
	}
	else if (Application::GetAsset()->GetScene() == SCENE_ASSET::GAME) {
		sp->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::WHITE));
	}
	sp->GetImage()->Set2DSize(D3DXVECTOR3(1920.0f, 1080.0f, 0));
	sp->GetImage()->Set2DPosition(D3DXVECTOR3(0, 0, 0));
	sp->GetImage()->SetColor(D3DXVECTOR4(1, 1, 1, 1));

	mSprite = sp;

}

void Fade::Uninit() {

	mSprite->Destroy();
}

void Fade::Update() {

	if (!mIsFade) {
		return;
	}

	mAlpha += mAddAlpha;

	if (mbOut) {
		if (mAlpha >= 1.0f) {
			mAlpha = 1.0f;
			mIsFade = false;
		}
	}
	else {
		if (mAlpha <= 0.0f) {
			mAlpha = 0.0f;
			mIsFade = false;
		}
	}

}

void Fade::Render() {

	if (mAlpha == 0.0f) {
		return;
	}

	mFadeColor.a = mAlpha;
	D3DCOLOR c = mFadeColor;

	/*mSprite->SetColor(D3DXVECTOR4(mFadeColor.r, mFadeColor.g, mFadeColor.b, mFadeColor.a));
	mSprite->Render();*/

}


void Fade::Start(bool bOut, int frame, D3DCOLOR color)
{
	mbOut = bOut;
	mAddAlpha = 1.0f / frame;
	mFadeColor = color;
	mIsFade = true;

	if (mbOut) {
		mAlpha = 0.0f;
	}
	else {
		mAlpha = 1.0f;
		mAddAlpha = -mAddAlpha;
	}
}
