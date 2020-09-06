#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "GUI.h"

void GUI::Init() {

	Sprite* sp = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp->Name = "Icon";
	sp->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::SAMURAI));
	sp->SetPosition(D3DXVECTOR2(100, 900));

	Sprite* sp2 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp2->Name = "Icon";
	sp2->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::WIZARD));
	sp2->SetPosition(D3DXVECTOR2(300, 900));

	Sprite* sp3 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp3->Name = "Icon";
	sp3->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::WARRIOR));
	sp3->SetPosition(D3DXVECTOR2(500, 900));

	Sprite* sp4 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp4->Name = "Icon";
	sp4->SetTexture(Application::GetAsset()->GetTexture(TEXTURE_ENUM::ELF));
	sp4->SetPosition(D3DXVECTOR2(700, 900));

	Gauge* hp = Application::GetScene()->AddGameObject<Gauge>(SpriteLayer);
	hp->Position = D3DXVECTOR3(900, 900, 0);
	hp->SetGUI(900);

	Digit* hp_digit = Application::GetScene()->AddGameObject<Digit>(SpriteLayer);
	hp_digit->Position = hp->Position + D3DXVECTOR3(350,25,0);
	hp_digit->MakeSprite(5,D3DXVECTOR2(48,48));

	// SavePtr
	mpPlayerHP = hp;
	mpPlayerHPDigit = hp_digit;

	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
}

void GUI::Update() {

	std::vector <Sprite*> sp = Application::GetScene()->GetGameObjects<Sprite>(SpriteLayer);;

	for (int i = 0; i < sp.size(); i++) {

		if (sp[i]->Name == "Icon") {
			if (i == mpPlayer->mNowController) {
				sp[i]->SetColor(D3DXVECTOR4(1,0,0,1));
			}
			else {
				sp[i]->SetColor(D3DXVECTOR4(1, 1, 1, 1));
			}
		}

	}

	mpPlayerHP->mFillAmount = mpPlayer->mHp / mpPlayer->GetHpInit();
	mpPlayerHPDigit->SetValue((int)mpPlayer->mHp);
}

