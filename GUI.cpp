#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "GUI.h"
#include "ImageManager.h"
#include "Digit.h"

void GUI::Init() {


	Sprite* Round_fr = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer2);
	Round_fr->Name = "RoundFrame";
	Round_fr->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::ROUND_FRAME));
	Round_fr->Position = D3DXVECTOR3(50, 50, 1);
	Round_fr->GetImage()->Set2DSize(D3DXVECTOR3(100, 100, 1));

	Sprite* cha_icon = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer2);
	cha_icon->Name = "cha_icon_0";
	cha_icon->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::CHARACTERICON_0));
	cha_icon->Position = D3DXVECTOR3(57, 57, 1);
	cha_icon->GetImage()->Set2DSize(D3DXVECTOR3(85, 85, 1));

	Gauge* Hp_Gauge = Application::GetScene()->AddGameObject<Gauge>(SpriteLayer);
	Hp_Gauge->Position = D3DXVECTOR3(Round_fr->GetImage()->GetSize().x + 15, Round_fr->GetImage()->GetSize().y - 30, 0);
	Hp_Gauge->SetGUI(600);

	mpPlayerHP = Hp_Gauge;
	mpPlayerIcon = cha_icon;
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
}

void GUI::Update() {

	mpPlayerHP->mFillAmount = mpPlayer->mHp / mpPlayer->GetHpInit();
}

