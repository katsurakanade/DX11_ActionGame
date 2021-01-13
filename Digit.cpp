#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Digit.h"
#include "ImageManager.h"

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
			mNumberSprite[i]->GetImage()->SetFrame(n);
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
		sp->GetImage()->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_GAME::NUMBER));
		sp->GetImage()->SetAnimationSprite(true);
		sp->GetImage()->SetHW(5, 5);
		sp->GetImage()->Set2DSize(D3DXVECTOR3(size.x, size.y, 1));
		sp->GetImage()->Set2DPosition(D3DXVECTOR3(Position.x + (size.x * (mFig - (i + 1.0f))), Position.y, 0.0f));

		mNumberSprite[i] = sp;
	}
} 

