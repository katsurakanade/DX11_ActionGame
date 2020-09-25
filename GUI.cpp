#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "GUI.h"

void GUI::Init() {

	Sprite* fr_0 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_0->Name = "Frame_0";
	fr_0->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_0->SetPosition(D3DXVECTOR3(200,875,1));
	fr_0->SetSize(D3DXVECTOR3(100,175,1));

	Sprite* fr_1 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_1->Name = "Frame_1";
	fr_1->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_1->SetPosition(D3DXVECTOR3(200, 675, 1));
	fr_1->SetSize(D3DXVECTOR3(100, 175, 1));

	Sprite* fr_2 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_2->Name = "Frame_2";
	fr_2->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_2->SetPosition(D3DXVECTOR3(75, 800, 1));
	fr_2->SetSize(D3DXVECTOR3(100, 175, 1));

	Sprite* fr_3 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	fr_3->Name = "Frame_3";
	fr_3->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::FRAME));
	fr_3->SetPosition(D3DXVECTOR3(325, 800, 1));
	fr_3->SetSize(D3DXVECTOR3(100, 175, 1));

	Sprite* Round_fr = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer2);
	Round_fr->Name = "RoundFrame";
	Round_fr->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::ROUND_FRAME));
	Round_fr->SetPosition(D3DXVECTOR3(50, 50, 1));
	Round_fr->SetSize(D3DXVECTOR3(100, 100, 1));

	Gauge* Hp_Gauge = Application::GetScene()->AddGameObject<Gauge>(SpriteLayer);
	Hp_Gauge->Position = D3DXVECTOR3(Round_fr->GetSize().x + 15, Round_fr->GetSize().y - 30, 0);
	Hp_Gauge->SetGUI(600);

	//Sprite* Item_0 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer2);
	//Item_0->Name = "Item_0";
	//Item_0->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::SWORD_ICON));
	//Item_0->SetPosition(D3DXVECTOR3(210, 890, 1));
	//Item_0->SetSize(D3DXVECTOR3(75, 145, 1));

	mpPlayerHP = Hp_Gauge;
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
}

void GUI::Update() {

	mpPlayerHP->mFillAmount = mpPlayer->mHp / mpPlayer->GetHpInit();
}

