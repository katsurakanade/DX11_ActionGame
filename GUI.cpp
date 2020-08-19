#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Sprite.h"
#include "Scene.h"
#include "GUI.h"

void GUI::Init() {

	Sprite* sp = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp->SetTexture(Asset::GetTexture(TEXTURE_ENUM::SAMURAI));
	sp->SetPosition(D3DXVECTOR2(100, 900));

	Sprite* sp2 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp2->SetTexture(Asset::GetTexture(TEXTURE_ENUM::WIZARD));
	sp2->SetPosition(D3DXVECTOR2(300, 900));

	Sprite* sp3 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp3->SetTexture(Asset::GetTexture(TEXTURE_ENUM::WARRIOR));
	sp3->SetPosition(D3DXVECTOR2(500, 900));

	Sprite* sp4 = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
	sp4->SetTexture(Asset::GetTexture(TEXTURE_ENUM::ELF));
	sp4->SetPosition(D3DXVECTOR2(700, 900));

	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
}

void GUI::Update() {

	std::vector <Sprite*> sp = Application::GetScene()->GetGameObjects<Sprite>(SpriteLayer);;

	for (int i = 0; i < 4; i++) {
		if (i == mpPlayer->mNowController) {
			sp[i]->SetPosition(D3DXVECTOR2((i * 200) + 100, 850));
		}
		else {
			sp[i]->SetPosition(D3DXVECTOR2((i * 200) + 100, 900));
		}
	}


}

