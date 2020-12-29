#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"
#include "Player.h"
#include "BossBehavior.h"
#include "Enemy.h"
#include <functional>  


void BossBehavior::Init() {

	EnemyBehavior::Init();

	mStatemap[BEHAVIOR_STATE_BOSS::Idle] = "Idle";
	mStatemap[BEHAVIOR_STATE_BOSS::Chase] = "Chase";
	mStatemap[BEHAVIOR_STATE_BOSS::Attack] = "Attack";
	mStatemap[BEHAVIOR_STATE_BOSS::Summon] = "Summon";
	mStatemap[BEHAVIOR_STATE_BOSS::Dying] = "Dying";

	mHpInit = 500.0f;
	mHp = mHpInit;

	mCoolSummon = 0.0f;
	mUsedSummon = false;
}

void BossBehavior::Uninit() {
	EnemyBehavior::Uninit();
}

void BossBehavior::Update() {

	EnemyBehavior::Update();

	unsigned int enemyalive = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer).size();

	if (enemyalive < 4) {
		mCoolSummon += Time::GetDeltaTime();
	}

	Summonprocess();

	// 行動決め
	if (mHp > 0.0f) {

		if (mState == "Idle" && mCoolSummon >= 7.0f) {
			mCoolSummon = 0.0f;
			mState = "Summon";
		}

	}
	else if (mHp <= 0.0f) {
		mState = "Dying";
	}

	// 行動
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
	else if (mState == "Summon" && enemyalive < 4) {
		mUsedSummon = true;
		mSummonThread = std::thread(&BossBehavior::Summon, this);
		mState = "Idle";
	}
	else if (mState == "Dying") {
		Dying();
	}

}

void BossBehavior::FixedUpdate() {
	EnemyBehavior::FixedUpdate();
}
void BossBehavior::DataPanel() {
	EnemyBehavior::DataPanel();

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"行為")) {
		ImGui::Text("State : %s", mState);
		ImGui::Text("LengthToPlayer : %f", mLengthToPlayer);
		ImGui::Text("DeadTimer : %f", mDeadTimer);
		ImGui::Text(u8"召喚クールタイム %f ", mCoolSummon);
		ImGui::TreePop();
	}
	ImGui::End();
}

void  BossBehavior::Summonprocess() {

	if (mUsedSummon)
		mSummonThreadWaitTime += Time::GetDeltaTime();

	if (mSummonThreadWaitTime > 0.5f) {
		mSummonenemy->StandBy = true;
		mSummonThread.join();
		mSummonThreadWaitTime = 0.0f;
		mUsedSummon = false;
	}
}

void BossBehavior::Summon() {

	std::uniform_real_distribution<float> rndx(-70, 70);

	mSummonenemy = Application::GetScene()->AddGameObject<Enemy>(ObjectLayer);
	mSummonenemy->StandBy = false;
	mSummonenemy->Name = "Enemy";
	mSummonenemy->Position = Position;
	mSummonenemy->Position.x += rndx(Application::RandomGen);
	mSummonenemy->Create();
	
}