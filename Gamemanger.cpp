#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Gamemanger.h"
#include "Enemy.h"

void Gamemanger::Init() {

}

void Gamemanger::Update() {


	if (mState == RoundState::ENEMY_ROUND) {

		Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
		std::vector <Enemy*> elist = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

		for (Enemy* e : elist) {
			e->Attack();
		}

		mState = RoundState::PLAYER_ROUND;
	}

	
}