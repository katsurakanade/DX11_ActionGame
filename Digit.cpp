#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Digit.h"

void Digit::Init() {

}

void Digit::Unint() {

}

void Digit::Update() {

	int count_stop_score = 1;
	for (int i = 0; i < mFig; i++) {
		count_stop_score *= 10;
	}

	if (mValue >= count_stop_score) {
		mValue = count_stop_score - 1;
	}

	int value = mValue;
	for (int i = 0; i < mFig; i++) {
		int n = value % 10;
		value /= 10;

		if (mNumberSprite.size() > 0) {
			mNumberSprite[i]->SetFrame(n);
		}
		else if (mNumberBillboard.size() > 0) {
			mNumberBillboard[i]->SetFrame(n);
			mNumberBillboard[i]->Position = D3DXVECTOR3(Position.x + (1.0f * (mFig - (i + 1.0f))), Position.y, Position.z);
		}
	}

}

void Digit::Render() {


}

void Digit::MakeSprite(int fig,D3DXVECTOR2 size) {

	mFig = fig;

	mNumberSprite.resize(mFig);

	for (int i = 0; i < mFig; i++) {

		Sprite* sp = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
		sp->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::NUMBER));
		sp->SetAnimationSprite(true);
		sp->SetHW(5, 5);
		sp->SetSize(D3DXVECTOR3(size.x, size.y, 1));
		sp->Position = D3DXVECTOR3(Position.x + (size.x * (mFig - (i + 1.0f))), Position.y, 0.0f);

		mNumberSprite[i] = sp;
	}
} 

void Digit::MakeBillBoard(int fig, D3DXVECTOR2 size) {

	mFig = fig;

	mNumberBillboard.resize(mFig);

	for (int i = 0; i < mFig; i++) {

		Effect* sp = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
		sp->Name = "digit";
		sp->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::NUMBER));
		sp->SetHW(5, 5);
		sp->SetLoop(true);
		sp->Scale = D3DXVECTOR3(size.x, size.y, 1);
		sp->Position = D3DXVECTOR3(Position.x + (size.x * (mFig - (i + 1.0f))), Position.y, Position.z);

		mNumberBillboard[i] = sp;
	}

}