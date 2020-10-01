#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "Gauge.h"

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

	if (mType == GaugeType::GAUGE_GUI) {
		std::vector <Sprite*> sp = Application::GetScene()->GetGameObjects<Sprite>(SpriteLayer);

		for (unsigned int i = 0; i < sp.size(); i++) {
			if (sp[i]->Name == "hpbarfill") {
				sp[i]->SetSize(D3DXVECTOR3(mGuiLength * mFillAmount, 100, 0));
			}
		}

	}

	else if (mType == GaugeType::GAUGE_BILLBOARD) {

		mpBar_empty->Position = mpTarget->Position + mPositionOffest;

		mpBar_fill->Position = mpTarget->Position + mPositionOffest;
		mpBar_fill->SetFillAmount(mFillAmount);
	}


}

void Gauge::Render() {

}

void Gauge::SetGUI(int length) {

	mType = GaugeType::GAUGE_GUI;

	Sprite* hpbar_empty = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	hpbar_empty->Name = "hpbarGUI";
	hpbar_empty->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_EMPTY));
	hpbar_empty->SetSize(D3DXVECTOR3((float)length, 25, 0));
	hpbar_empty->SetPosition(D3DXVECTOR3(Position.x, Position.y,1));

	Sprite* hpbar_fill = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	hpbar_fill->Name = "hpbarfillGUI";
	hpbar_fill->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_FILL));
	hpbar_fill->SetSize(D3DXVECTOR3((float)length, 25, 0));
	hpbar_fill->Position = D3DXVECTOR3(Position.x, Position.y, 0);
	hpbar_fill->SetFillSprite(true);

	mGuiLength = length;
}

void Gauge::SetBillBoard(Resource* target) {

	mType = GaugeType::GAUGE_BILLBOARD;

	Effect* hpbar_empty = Application::GetScene()->AddGameObject<Effect>(ObjectLayer);
	hpbar_empty->Name = "hpbar";
	hpbar_empty->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_EMPTY));
	hpbar_empty->SetHW(1, 1);
	hpbar_empty->SetLoop(true);
	hpbar_empty->Scale = D3DXVECTOR3(4.0f, 0.5f, 1.0f);

	Effect* hpbar_fill = Application::GetScene()->AddGameObject<Effect>(ObjectLayer);
	hpbar_fill->Name = "hpbarfill";
	hpbar_fill->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BAR_FILL));
	hpbar_fill->SetHW(1, 1);
	hpbar_fill->SetLoop(true);
	hpbar_fill->Scale = D3DXVECTOR3(4.0f, 0.5f, 1.0f);

	mpBar_empty = hpbar_empty;
	mpBar_fill = hpbar_fill;

	mpTarget = target;
}