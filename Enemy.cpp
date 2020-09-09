#include "main.h"
#include "Renderer.h"
#include "Scene.h"
#include "Application.h"
#include "Enemy.h"
#include "Ball.h"
#include "Player.h"
#include "Physical.h"

int Enemy::ID;

void Enemy::Init() {

	Name = "Enemy_" + std::to_string(ID);

	//mModel = Application::GetAsset()->GetAssimpModel(ASSIMP_MODEL_ENUM::ENEMY);

	Position = D3DXVECTOR3(0, 10, 0);
	Rotation = D3DXVECTOR3(1.72f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	D3DXQuaternionIdentity(&Quaternion);

	AddComponent<Physical>();
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->mPositionOffest = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	GetComponent<BoxCollider>()->mScaleOffest = D3DXVECTOR3(7.2f, 7.2f, 7.2f);

	Resource::Init();

	ID++;
}

void Enemy::AddGauge() {

	Gauge* gauge = Application::GetScene()->AddGameObject<Gauge>(ObjectLayer);
	gauge->SetBillBoard(this);
	gauge->mPositionOffest = D3DXVECTOR3(0.0f, 2.0f, 9.0f);
	mGauge = gauge;

	mHpInit = 50.0f;
	mHp = mHpInit;
	mGauge->mFillAmount = mHp / mHpInit;

}

void Enemy::Uninit() {

	if (mGauge) {
		mGauge->Destroy();
	}

	Resource::Uninit();
}

void Enemy::Update() {

	std::vector<Ball*> PlayerList = Application::GetScene()->GetGameObjects<Ball>(ObjectLayer);

	for (Ball* trg : PlayerList) {

		BoxCollider* sbc = GetComponent<BoxCollider>();
		BoxCollider* tbc = trg->GetComponent<BoxCollider>();

		if (sbc->Collision_Box_Enter(tbc)) {

			// Self
			GetComponent<Physical>()->mSpeed = 10.0f;
			D3DXVECTOR3 dir = trg->Position - Position;
			D3DXVECTOR3 dirn;
			D3DXVec3Normalize(&dirn, &dir);
			GetComponent<Physical>()->mVelocity = dirn;

			// Target
			trg->GetComponent<Physical>()->SpeedDown(0.05f);
			
			// Effect
			Effect* obj = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
			obj->Position = Position;
			obj->SetHW(8, 6);
			mHp -= 2.0f;
		}
	}

	if (mHp <= 0) {
		Destroy();
	}

	mGauge->mFillAmount = mHp / mHpInit;

	Resource::Update();
}

void Enemy::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mModel->Draw(world);
	mGauge->Render();

	GetComponent<BoxCollider>()->Render();
}

void Enemy::Attack() {

	Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);

	p->mHp -= 1000.0f;
}