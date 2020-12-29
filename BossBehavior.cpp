#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"
#include "Player.h"
#include "BossBehavior.h"

void BossBehavior::Init() {
	EnemyBehavior::Init();
	mHpInit = 500.0f;
	mHp = mHpInit;
}
void BossBehavior::Uninit() {
	EnemyBehavior::Uninit();
}
void BossBehavior::Update() {

	// s“®Œˆ‚ß
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

	// s“®
	if (mState == "Idle") {
		mpAnimation->SetNewState("Idle");
	}
	else if (mState == "Chase") {
		/*mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position);*/
	}
	else if (mState == "Attack") {
		/*mpAnimation->SetNewStateOneTime("Attack", 0.8f);*/
	}
	else if (mState == "Dying") {
		Dying();
	}

	EnemyBehavior::Update();
}
void BossBehavior::FixedUpdate() {
	EnemyBehavior::FixedUpdate();
}
void BossBehavior::DataPanel() {
	EnemyBehavior::DataPanel();
}