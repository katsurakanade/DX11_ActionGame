#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"
#include "Player.h"
#include "Behavior.h"

void Behavior::Init() {

	// コンポーネント取得
	mpPhysical = GetResource()->GetComponent<Physical>();
	mpAnimation = GetResource()->GetComponent<Animation>();
	// プレイヤー取得
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
	// ステート初期化
	mState = BEHAVIOR_STATE::Idle;
}

void Behavior::Uninit() {

}

void Behavior::Update() {

	Position = GetResource()->Position;

	// 範囲計算
	D3DXVECTOR3 pp = mpPlayer->Position;
	D3DXVECTOR3 sp = Position;
	D3DXVECTOR3 direction = pp - sp;
	float length = D3DXVec3Length(&direction);

	ImGui::Begin(GetResource()->Name.c_str());
	ImGui::Text("Length : %f", length);
	ImGui::Text("State : %d", mState);
	ImGui::End();

	// 行動決め
	if (length < 10) 
		mState = BEHAVIOR_STATE::Attack;
	else if (length > 10 && length < 40) 
		mState = BEHAVIOR_STATE::Chase;
	else if (length > 40) 
		mState = BEHAVIOR_STATE::Idle;

	// 行動
	switch (mState)
	{
	case BEHAVIOR_STATE::Idle:
		mpAnimation->SetNewState("Idle");
		break;
	case BEHAVIOR_STATE::Chase:
		mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position);
		break;
	case BEHAVIOR_STATE::Attack:
		mpAnimation->SetNewStateOneTime("Attack",0.7f);
		break;
	default:
		break;
	}
}

void Behavior::FixedUpdate() {

	
}

void Behavior::Movement(int arrow) {

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

void Behavior::MoveTo(D3DXVECTOR3 target_position) {

	D3DXVECTOR3 result;
	D3DXVECTOR3 direction = target_position - Position;
	D3DXVec3Normalize(&result, &direction);

	// TODO:8方向改善、角度改善
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
	
	if (mpPhysical->mAcceleration < 1.5f) 
		mpPhysical->mAcceleration += 0.05f;
	
	mpPhysical->mSpeed += mpPhysical->mAcceleration;
	mpPhysical->mVelocity = result;
}