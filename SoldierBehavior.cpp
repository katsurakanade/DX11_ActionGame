#include "main.h"
#include "Application.h"
#include "Renderer.h"

#include "Resource.h"
#include "Animation.h"
#include "Physical.h"
#include "Player.h"
#include "SoldierBehavior.h"
#include "Time.h"

void SoldierBehavior::Init() {

	EnemyBehavior::Init();

	// �X�e�[�g������
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

	// �s������
	ChooseAction();

	// �s��
	RunAction();
}

void SoldierBehavior::FixedUpdate() {
	EnemyBehavior::FixedUpdate();
}

void SoldierBehavior::DataPanel() {
	EnemyBehavior::DataPanel();
}

void SoldierBehavior::ChooseAction(){

	if (mHp > 0.0f) {
		if (mLengthToPlayer < 10) {
			mAttackWaitTime += Time::GetDeltaTime();
			if (mAttackWaitTime >= 1.2f) {
				mState = "Attack";
			}
		}
		else if (mLengthToPlayer > 10 && mLengthToPlayer < 40) {
			mAttackWaitTime = 0.0f;
			mState = "Chase";
		}
		else if (mLengthToPlayer > 40) {
			mAttackWaitTime = 0.0f;
			mState = "Idle";
		}
	}
	else if (mHp <= 0.0f) {
		mState = "Dying";
	}
}

void SoldierBehavior::RunAction() {

	if (mState == "Idle") {
		mpAnimation->SetNewState("Idle");
	}
	else if (mState == "Chase") {
		mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position);
	}
	else if (mState == "Attack") {
		mpAnimation->SetNewStateOneTime("Attack", 0.8f);
		mpPlayer->mHp -= 30.0f;
	}
	else if (mState == "Dying") {
		Dying();
	}
}