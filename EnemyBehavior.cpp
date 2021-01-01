#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"
#include "Player.h"
#include "EnemyBehavior.h"
#include <map>

void EnemyBehavior::Init() {

	// �R���|�[�l���g�擾
	mpPhysical = GetResource()->GetComponent<Physical>();
	mpAnimation = GetResource()->GetComponent<Animation>();
	// �v���C���[�擾
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
	mDeadTimer = 0.0f;
	// ������
	mState = "Idle";

	std::uniform_real_distribution<float> rndx(1.0f, 1.5f);
	std::uniform_real_distribution<float> rndy(0.01f, 0.07f);

	mMaxSpeedChase = rndx(Application::RandomGen);
	mPlusSpeedChase = rndy(Application::RandomGen);
}

void EnemyBehavior::Uninit() {

}

void EnemyBehavior::Update() {

	Position = GetResource()->Position;

	// �͈͌v�Z
	D3DXVECTOR3 pp = mpPlayer->Position;
	D3DXVECTOR3 sp = Position;
	D3DXVECTOR3 direction = pp - sp;
	mLengthToPlayer = D3DXVec3Length(&direction);

}

void EnemyBehavior::FixedUpdate() {

	if (mDeadTimer >= 2.5f) {
		GetResource()->Destroy();
	}

	Component::FixedUpdate();
}

void EnemyBehavior::DataPanel() {

}

void EnemyBehavior::Movement(int arrow) {

	switch (arrow)
	{
	case 0:
		Rotation.y = D3DX_PI * 0.25f;

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}

		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));
		break;
	case 1:

		Rotation.y = D3DX_PI * -0.25f;

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}
		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));
		break;
	case 2:
		Rotation.y = D3DX_PI * 0.75f;

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}

		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));
		break;
	case 3:
		Rotation.y = D3DX_PI * -0.75f;

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}
		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));
		break;
	case 4:
		if (Rotation.y != 1.72f) {
			Rotation = D3DXVECTOR3(0.0f, 1.72f, 0.0f);
		}

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}
		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(-1.0f, 0, 0);
		break;
	case 5:
		if (Rotation.y != -1.72f) {
			Rotation = D3DXVECTOR3(0.0f, -1.72f, 0.0f);
		}

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}
		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(1.0f, 0, 0);
		break;
	default:
		break;
	}

}

void EnemyBehavior::MoveTo(D3DXVECTOR3 target_position) {

	D3DXVECTOR3 result;
	D3DXVECTOR3 direction = target_position - Position;
	D3DXVec3Normalize(&result, &direction);

	// TODO:�p�x���P
	if (direction.z > 5.0f) {
		if (direction.x > -4.0f && direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 1.0f;
		else if (direction.x > 4.0f)
			GetResource()->Rotation.y = D3DX_PI * -0.75f;
		else if (direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 0.75f;
	}
	else if (direction.z < 5.0f && direction.z > -5.0f) {
		if (direction.x > 0.0f)
			GetResource()->Rotation.y = D3DX_PI * -0.5f;
		else if (direction.x < 0.0f)
			GetResource()->Rotation.y = D3DX_PI * 0.5f;
	}
	else if (direction.z < -5.0f) {
		if (direction.x > -4.0f && direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 2.0f;
		else if (direction.x > 4.0f)
			GetResource()->Rotation.y = D3DX_PI * -0.25f;
		else if (direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 0.25f;
	}
	
	if (mpPhysical->mAcceleration < mMaxSpeedChase)
		mpPhysical->mAcceleration += mPlusSpeedChase;
	
	mpPhysical->mSpeed += mpPhysical->mAcceleration;
	mpPhysical->mVelocity = result;
}

void EnemyBehavior::LookAt(D3DXVECTOR3 target_position) {

	D3DXVECTOR3 result;
	D3DXVECTOR3 direction = target_position - Position;
	D3DXVec3Normalize(&result, &direction);

	// TODO:�p�x���P
	if (direction.z > 5.0f) {
		if (direction.x > -4.0f && direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 1.0f;
		else if (direction.x > 4.0f)
			GetResource()->Rotation.y = D3DX_PI * -0.75f;
		else if (direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 0.75f;
	}
	else if (direction.z < 5.0f && direction.z > -5.0f) {
		if (direction.x > 0.0f)
			GetResource()->Rotation.y = D3DX_PI * -0.5f;
		else if (direction.x < 0.0f)
			GetResource()->Rotation.y = D3DX_PI * 0.5f;
	}
	else if (direction.z < -5.0f) {
		if (direction.x > -4.0f && direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 2.0f;
		else if (direction.x > 4.0f)
			GetResource()->Rotation.y = D3DX_PI * -0.25f;
		else if (direction.x < 4.0f)
			GetResource()->Rotation.y = D3DX_PI * 0.25f;
	}

}

void EnemyBehavior::Dying() {

	Camera* camera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);

	if (camera) {
		camera->SetLookTarget(nullptr);
	}

	if (mpAnimation->GetNewState() != "Dying") {
		mpAnimation->SetNewStateOneTime("Dying", 2.5f);
	}

	mDeadTimer += Time::GetDeltaTime();

}