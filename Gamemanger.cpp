#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Gamemanger.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Player.h"


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
		
	Application::GetScene()->SetSwitchFlag(true);
}

