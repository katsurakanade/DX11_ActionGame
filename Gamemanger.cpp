#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Gamemanger.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Player.h"
#include "StaticManger.h"


void Gamemanger::Init() {

	Name = "GameManger";
	mRound = 0;

	mpLevel = Application::GetScene()->GetGameObject<Level>(ObjectLayer);
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

	/*if (!mGameClear && enemylist.size() == 0) {
		mRound++;
		mpLevel->SetRound(mRound);
	}

	if (mRound == 3 && enemylist.size() == 0) {
		mGameClear = true;
		GameClear(true);
	}*/

	else if (!mGameClear && Application::GetScene()->GetGameObject<Player>(ObjectLayer)->mHp <= 0) {
		GameClear(false);
	}
}

void Gamemanger::GameClear(bool win) {
		
	Application::GetScene()->SetSwitchFlag(true);

	if (win) {
		StaticManger::StateMap["GameClear"] = "true";
	}

	else if (!win) {
		StaticManger::StateMap["GameClear"] = "false";
	}
}

