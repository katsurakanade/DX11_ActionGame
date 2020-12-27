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

	// コンポーネント取得
	mpPhysical = GetResource()->GetComponent<Physical>();
	mpAnimation = GetResource()->GetComponent<Animation>();
	// プレイヤー取得
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
	// ステート初期化
	mStatemap[BEHAVIOR_STATE::Idle] = "Idle";
	mStatemap[BEHAVIOR_STATE::Chase] = "Chase";
	mStatemap[BEHAVIOR_STATE::Attack] = "Attack";
}

void EnemyBehavior::Uninit() {

}

void EnemyBehavior::Update() {

	Position = GetResource()->Position;

	// 範囲計算
	D3DXVECTOR3 pp = mpPlayer->Position;
	D3DXVECTOR3 sp = Position;
	D3DXVECTOR3 direction = pp - sp;
	mLengthToPlayer = D3DXVec3Length(&direction);

	// 行動決め
	if (mLengthToPlayer < 10)
		mState = "Attack";
	else if (mLengthToPlayer > 10 && mLengthToPlayer < 40)
		mState = "Chase";
	else if (mLengthToPlayer > 40)
		mState = "Idle";

	// 行動
	if (mState == "Idle") {
		mpAnimation->SetNewState("Idle");
	}
	else if (mState == "Chase") {
		mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position);
	}
	else if (mState == "Attack") {
		mpAnimation->SetNewStateOneTime("Attack", 0.7f);
	}



}

void EnemyBehavior::FixedUpdate() {

	Component::FixedUpdate();
}

void EnemyBehavior::DataPanel() {

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"行為")) {
		ImGui::Text("State : %s", mState);
		ImGui::Text("LengthToPlayer : %f", mLengthToPlayer);
		ImGui::TreePop();
	}
	ImGui::End();
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

	// TODO:角度改善
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