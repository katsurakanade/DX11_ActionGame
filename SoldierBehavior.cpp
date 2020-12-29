#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"
#include "Player.h"
#include "SoldierBehavior.h"


void SoldierBehavior::Init() {

	EnemyBehavior::Init();

	// ステート初期化
	mStatemap[BEHAVIOR_STATE_SOLDIER::Idle] = "Idle";
	mStatemap[BEHAVIOR_STATE_SOLDIER::Chase] = "Chase";
	mStatemap[BEHAVIOR_STATE_SOLDIER::Attack] = "Attack";
	mStatemap[BEHAVIOR_STATE_SOLDIER::Dying] = "Dying";

	mHpInit = 50.0f;
	mHp = mHpInit;
}
void SoldierBehavior::Uninit() {
	EnemyBehavior::Uninit();
}
void SoldierBehavior::Update() {

	EnemyBehavior::Update();

	// 行動決め
	if (mHp > 0.0f) {
		if (mLengthToPlayer < 10)
			mState = "Attack";
		else if (mLengthToPlayer > 10 && mLengthToPlayer < 40)
			mState = "Chase";
		else if (mLengthToPlayer > 40)
			mState = "Idle";
	}
	else if (mHp <= 0.0f) {
		mState = "Dying";
	}

	// 行動
	if (mState == "Idle") {
		mpAnimation->SetNewState("Idle");
	}
	else if (mState == "Chase") {
		mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position);
	}
	else if (mState == "Attack") {
		mpAnimation->SetNewStateOneTime("Attack", 0.8f);
	}
	else if (mState == "Dying") {
		Dying();
	}
}
void SoldierBehavior::FixedUpdate() {
	EnemyBehavior::FixedUpdate();
}
void SoldierBehavior::DataPanel() {
	EnemyBehavior::DataPanel();
}