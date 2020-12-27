#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "GUI.h"
#include "ImageManager.h"
#include "Digit.h"

void GUI::Init() {

	Sprite* fr_0 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_0->Name = "Frame_0";
	fr_0->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_0->Position = D3DXVECTOR3(200, 875, 1);
	fr_0->GetImage()->Set2DSize(D3DXVECTOR3(100,175,1));

	Sprite* fr_1 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_1->Name = "Frame_1";
	fr_1->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_1->Position = D3DXVECTOR3(200, 675, 1);
	fr_1->GetImage()->Set2DSize(D3DXVECTOR3(100, 175, 1));

	Sprite* fr_2 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_2->Name = "Frame_2";
	fr_2->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_2->Position = D3DXVECTOR3(75, 800, 1);
	fr_2->GetImage()->Set2DSize(D3DXVECTOR3(100, 175, 1));

	Sprite* fr_3 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_3->Name = "Frame_3";
	fr_3->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_3->Position = D3DXVECTOR3(325, 800, 1);
	fr_3->GetImage()->Set2DSize(D3DXVECTOR3(100, 175, 1));

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

