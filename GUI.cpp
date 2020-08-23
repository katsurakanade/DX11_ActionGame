#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "GUI.h"

void GUI::Init() {

	Sprite* sp = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp->Name = "Icon";
	sp->SetTexture(Asset::GetTexture(TEXTURE_ENUM::SAMURAI));
	sp->SetPosition(D3DXVECTOR2(100, 900));

	Sprite* sp2 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp2->Name = "Icon";
	sp2->SetTexture(Asset::GetTexture(TEXTURE_ENUM::WIZARD));
	sp2->SetPosition(D3DXVECTOR2(300, 900));

	Sprite* sp3 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp3->Name = "Icon";
	sp3->SetTexture(Asset::GetTexture(TEXTURE_ENUM::WARRIOR));
	sp3->SetPosition(D3DXVECTOR2(500, 900));

	Sprite* sp4 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp4->Name = "Icon";
	sp4->SetTexture(Asset::GetTexture(TEXTURE_ENUM::ELF));
	sp4->SetPosition(D3DXVECTOR2(700, 900));

	Gauge* hp = Application::GetScene()->AddGameObject<Gauge>(SpriteLayer);
	hp->SetGUI(900);

	// SavePtr
	mpPlayerHP = hp;

	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
}

void GUI::Update() {

	std::vector <Sprite*> sp = Application::GetScene()->GetGameObjects<Sprite>(SpriteLayer);;

	for (int i = 0; i < sp.size(); i++) {

		if (sp[i]->Name == "Icon") {
			if (i == mpPlayer->mNowController) {
				sp[i]->SetPosition(D3DXVECTOR2((i * 200.0f) + 100.0f, 850.0f));
			}
			else {
				sp[i]->SetPosition(D3DXVECTOR2((i * 200.0f) + 100.0f, 900.0f));
			}
		}

	}

	mpPlayerHP->mFillAmount = mpPlayer->mHp / mpPlayer->GetHpInit();
}

