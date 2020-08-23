#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Gamemanger.h"
#include "Enemy.h"
#include "Sprite.h"

void Gamemanger::Init() {

}

void Gamemanger::Update() {

	std::vector <Enemy*> enemylist = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

	if (mState == RoundState::ENEMY_ROUND) {

		Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
		std::vector <Enemy*> elist = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

		for (Enemy* e : elist) {
			e->Attack();
		}

		mState = RoundState::PLAYER_ROUND;
	}

	if (!mGameClear && enemylist.size() == 0) {
		GameClear();
	}

	
}

void Gamemanger::GameClear() {
	/*Sprite* clear = Application::GetScene()->AddGameObject<Sprite>(SpriteLayer);
		clear->Name = "GameClearSprite";
		clear->SetTexture(Asset::GetTexture(TEXTURE_ENUM::CLEAR));
		clear->SetSize(D3DXVECTOR3(800.0f, 500.0f, 1.0f));
		clear->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2 - 400.0f, 100.0f));
		mGameClear = true;*/
}

