#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Player.h"
#include "Ball.h"

void Player::Init() {

	mNowController = 1;

	Ball* b1 = Application::GetScene()->AddGameObject<Ball>(ObjectLayer);
	b1->Name = "Ball";
	b1->Rotation = D3DXVECTOR3(-0.5f, 1.72f, 1.72f);
	b1->SetModelTexture(0);
	b1->InitArrowPosition();
	b1->SetArrow(false);

	Ball* b2= Application::GetScene()->AddGameObject<Ball>(ObjectLayer);
	b2->Name = "Ball2";
	b2->Position = D3DXVECTOR3(10, 10, 0);
	b2->Rotation = D3DXVECTOR3(0.5f, 1.72f, 1.72f);
	b2->SetModelTexture(1);
	b2->InitArrowPosition();
	b2->SetArrow(true);

}

void Player::SelectBall() {

	std::vector<Ball*> Balllist = Application::GetScene()->GetGameObjects<Ball>(ObjectLayer);

	if (mNowController == 0) {
		Balllist[0]->InitArrowPosition();
		Balllist[0]->SetArrow(true);
		Balllist[1]->SetArrow(false);
	}

	if (mNowController == 1) {
		Balllist[1]->InitArrowPosition();
		Balllist[0]->SetArrow(false);
		Balllist[1]->SetArrow(true);
	}

}