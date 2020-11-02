#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "Gauge.h"
#include "ImageManager.h"

void Gauge::Init() {

	mFillAmount = 1.0f;

}

void Gauge::Uninit() {

	if (mpBar_empty) {
		mpBar_empty->Destroy();
	}
	if (mpBar_fill) {
		mpBar_fill->Destroy();
	}

}

void Gauge::Update() {

	// GUI
	if (mType == GaugeType::GAUGE_GUI) {
		mpBar_fill->GetImage()->SetFillAmount(mFillAmount);
		mpBar_fill->Position = D3DXVECTOR3(Position.x, Position.y, 1);
		mpBar_fill->GetImage()->Set2DSize(D3DXVECTOR3(mGuiLength * mFillAmount, 25, 0));
	}

	// ビルボード
	else if (mType == GaugeType::GAUGE_BILLBOARD) {

		mpBar_empty->Position = mpTarget->Position + mPositionOffest;

		mpBar_fill->Position = mpTarget->Position + mPositionOffest;
		mpBar_fill->GetImage()->SetFillAmount(mFillAmount);
		
		mpBar_empty->Position = mpBar_fill->Position;
	}



}

void Gauge::Render() {

}

void Gauge::SetGUI(int length) {

	mType = GaugeType::GAUGE_GUI;

	Sprite* hpbar_empty = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	hpbar_empty->Name = "hpbarGUI";
	hpbar_empty->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_EMPTY));
	hpbar_empty->GetImage()->Set2DSize(D3DXVECTOR3((float)length, 25, 0));
	hpbar_empty->Position = D3DXVECTOR3(Position.x, Position.y, 1);

	Sprite* hpbar_fill = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	hpbar_fill->Name = "hpbarfillGUI";
	hpbar_fill->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_FILL));
	hpbar_fill->GetImage()->Set2DSize(D3DXVECTOR3((float)length, 25, 0));
	hpbar_fill->Position = D3DXVECTOR3(Position.x, Position.y, 1);

	mpBar_empty = hpbar_empty;
	mpBar_fill = hpbar_fill;

	mGuiLength = length;
}

void Gauge::SetBillBoard(Resource* target) {

	mType = GaugeType::GAUGE_BILLBOARD;

	Sprite* hpbar_empty = Application::GetScene()->AddGameObject<Sprite>(EffectLayer);
	hpbar_empty->Name = "hpbar";
	hpbar_empty->GetImage()->SetBillBoard(true);
	hpbar_empty->GetImage()->SetAnimationSprite(true);
	hpbar_empty->GetImage()->SetHW(1, 1);
	hpbar_empty->GetImage()->SetLoop(true);
	hpbar_empty->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_EMPTY));
	hpbar_empty->Position = D3DXVECTOR3(0, 0, 0);
	hpbar_empty->Scale = D3DXVECTOR3(7.0f, 0.5f, 1.0f);

	Sprite* hpbar_fill = Application::GetScene()->AddGameObject<Sprite>(EffectLayer);
	hpbar_fill->Name = "hpbarfill";
	hpbar_fill->GetImage()->SetBillBoard(true);
	hpbar_fill->GetImage()->SetAnimationSprite(true);
	hpbar_fill->GetImage()->SetHW(1, 1);
	hpbar_fill->GetImage()->SetLoop(true);
	hpbar_fill->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_FILL));
	hpbar_fill->Position = D3DXVECTOR3(0, 0, 0);
	hpbar_fill->Scale = D3DXVECTOR3(7.0f, 0.5f, 1.0f);

	mpBar_empty = hpbar_empty;
	mpBar_fill = hpbar_fill;

	mpTarget = target;
}