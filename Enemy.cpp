#include "main.h"
#include "Renderer.h"
#include "Scene.h"
#include "Application.h"
#include "Enemy.h"
#include "Ball.h"
#include "Player.h"
#include "Physical.h"
#include "Animation.h"
#include "input.h"
#include "Shader.h"

int Enemy::ID;

void Enemy::Init() {

	Name = "Enemy_" + std::to_string(ID);

	mModel = Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ENEMY);

	Position = D3DXVECTOR3(0, 12, -20);
	Rotation = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

	D3DXQuaternionIdentity(&Quaternion);

	AddComponent<Physical>();
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->mPositionOffest = D3DXVECTOR3(0.0f, 3.5f, 3.0f);
	GetComponent<BoxCollider>()->mScaleOffest = D3DXVECTOR3(3.2f, 7.14f, 3.2f);

	mpAnination = AddComponent<Animation>();
	mpAnination->SetState("Idle");
	mpAnination->SetCoefficient(10.0f);

	Resource::Init();

	change = 0;
	change_fr = rand() % (250 - 0 + 50) + 50;

	ID++;
}

void Enemy::AddGauge() {

	Gauge* gauge = Application::GetScene()->AddGameObject<Gauge>(ObjectLayer);
	gauge->SetBillBoard(this);
	gauge->mPositionOffest = D3DXVECTOR3(0.0f, 9.0f, 0.0f);
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

	change++;

	float speed = GetComponent<Physical>()->mSpeed;

	mModel->Update(mpAnination->GetState().c_str(), mpAnination->GetNewState().c_str(), mpAnination->GetBlend(), mpAnination->GetFrame());

	if (mpAnination->GetState() == "Idle" && speed >= 1.5f) {
		mpAnination->SetNewState("Running");
	}

	if (mpAnination->GetState() == "Running" && speed <= 1.0f) {
		mpAnination->SetNewState("Idle");
		mpAnination->SetCoefficient(20.0f);
	}

	if (mpAnination->GetNewState() == "Running") {
		mpAnination->SetCoefficient(20.0);
	}

	if (change > change_fr) {
		arrow = rand() % (5 - 0+ 1) + 0;
		change_fr = rand() % (250 - 0 + 50) + 50;
		change = 0;
	}

	if (start) {
		//Movement(arrow);
		LookAt();
	}

	if (Input::GetKeyTrigger(DIK_K)) {
		start = true;
	}

	if (mGauge) {
		mGauge->mFillAmount = mHp / mHpInit;
	}

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

	Shader::Use(SHADER_TYPE_VSPS::Default);

	mModel->Draw(world);
	
	GetComponent<BoxCollider>()->Render();
}

void Enemy::Attack() {

	Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);

	p->mHp -= 1000.0f;
}

void Enemy::Movement(int arrow) {

	switch (arrow)
	{
	case 0:
		Rotation.y = D3DX_PI * 0.25f;

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}

		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));
		break;
	case 1:

		Rotation.y = D3DX_PI * -0.25f;

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}
		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));
		break;
	case 2:
		Rotation.y = D3DX_PI * 0.75f;

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}

		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));
		break;
	case 3:
		Rotation.y = D3DX_PI * -0.75f;

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}
		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));
		break;
	case 4:
		if (Rotation.y != 1.72f) {
			Rotation = D3DXVECTOR3(0.0f, 1.72f, 0.0f);
		}

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}
		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-1.0f, 0, 0);
		break;
	case 5:
		if (Rotation.y != -1.72f) {
			Rotation = D3DXVECTOR3(0.0f, -1.72f, 0.0f);
		}

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}
		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(1.0f, 0, 0);
		break;
	default:
		break;
	}

}

void Enemy::LookAt() {

	Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);

	D3DXVECTOR3 pos = p->Position - Position;
	D3DXVECTOR3 result;
	D3DXVec3Normalize(&result, &pos);

	// LookAt Player
	//D3DXVECTOR3 a = GetForward()
	//D3DXVECTOR3 b;
	//D3DXVec3Normalize(&b, &a);

	//float theta = acos(D3DXVec2Dot(&result,&b));
	//Rotation = D3DXVECTOR3(0, -theta, 0);

	if (GetComponent<Physical>()->mAcceleration < 1.5f) {
		GetComponent<Physical>()->mAcceleration += 0.05f;
	}

	GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
	GetComponent<Physical>()->mVelocity = result;
}