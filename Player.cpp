#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Player.h"
#include "Ball.h"

void Player::Init() {

	mNowController = 0;

	Ball* b1 = Application::GetScene()->AddGameObject<Ball>(ObjectLayer);
	b1->Name = "Ball";
	b1->Rotation = D3DXVECTOR3(-0.5f, 1.72f, 1.72f);
	b1->SetModelTexture(0);
	b1->InitArrowPosition();
	b1->SetArrow(true);

	Ball* b2= Application::GetScene()->AddGameObject<Ball>(ObjectLayer);
	b2->Name = "Ball2";
	b2->Position = D3DXVECTOR3(10, 10, 0);
	b2->Rotation = D3DXVECTOR3(0.5f, 1.72f, 1.72f);
	b2->SetModelTexture(1);
	b2->InitArrowPosition();
	b2->SetArrow(false);

	Ball* b3 = Application::GetScene()->AddGameObject<Ball>(ObjectLayer);
	b3->Name = "Ball3";
	b3->Position = D3DXVECTOR3(30, 10, 0);
	b3->Rotation = D3DXVECTOR3(0.5f, 1.72f, 1.72f);
	b3->SetModelTexture(2);
	b3->InitArrowPosition();
	b3->SetArrow(false);

	Ball* b4= Application::GetScene()->AddGameObject<Ball>(ObjectLayer);
	b4->Name = "Ball4";
	b4->Position = D3DXVECTOR3(-15, 10, 0);
	b4->Rotation = D3DXVECTOR3(0.5f, 1.72f, 1.72f);
	b4->SetModelTexture(3);
	b4->InitArrowPosition();
	b4->SetArrow(false);

	mHp = mHpInit;
}

void Player::SelectBall() {

	std::vector<Ball*> Balllist = Application::GetScene()->GetGameObjects<Ball>(ObjectLayer);

	for (int i = 0; i < 4; i++) {
		if (i == mNowController) {
			Balllist[i]->InitArrowPosition();
			Balllist[i]->SetArrow(true);
		}
		else {
			Balllist[i]->SetArrow(false);
		}
	}

}