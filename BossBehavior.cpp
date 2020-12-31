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
	mCanUseSkill = true;

	mpAnimation->SetCoefficient(1.0f);
}

void BossBehavior::Uninit() {
	EnemyBehavior::Uninit();
}

void BossBehavior::Update() {

	EnemyBehavior::Update();

	Summonprocess();

	// �s������
	ChooseAction();

	// �s��
	RunAction();

}

void BossBehavior::FixedUpdate() {
	EnemyBehavior::FixedUpdate();
}

void BossBehavior::DataPanel() {
	EnemyBehavior::DataPanel();

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"�s��")) {
		ImGui::Text("State : %s", mState);
		ImGui::Text("LengthToPlayer : %f", mLengthToPlayer);
		ImGui::Text("DeadTimer : %f", mDeadTimer);
		ImGui::Text(u8"�����N�[���^�C�� %f ", mCoolSummon);
		ImGui::TreePop();
	}
	ImGui::End();
}

void BossBehavior::ChooseAction() {

	// �����Ă���G�̐�
	auto enemyalive = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer).size();
	if (enemyalive < 4 && mCanUseSkill) {
		mCoolSummon += Time::GetDeltaTime();
	}

	// �����Ă���
	if (mHp > 0.0f) {

		// �ҋ@���
		if (mState == "Idle") {
			// ->�U�����
			if (mLengthToPlayer < 20.0f) {
				mState = "Attack";
				mCanUseSkill = false;
			}
			// ->�������
			if (mCoolSummon >= 10.0f) {
				mState = "Summon";
			}
			
		}
		// �U�����
		else if (mState == "Attack") {
			// ->�ҋ@���
			if (mLengthToPlayer > 20.0f) {
				mState = "Idle";
				mCanUseSkill = true;
			}
		}

	}
	// ���S (-> ���S���)
	else if (mHp <= 0.0f) {
		mState = "Dying";
	}
}

void BossBehavior::RunAction() {

	if (mState == "Idle") {

	}
	else if (mState == "Chase") {
		mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position);
	}
	else if (mState == "Attack") {
		LookAt(mpPlayer->Position);
		mpAnimation->SetNewStateOneTime("Attack", 0.8f);
		mCoolSummon = 0.0f;
	}
	else if (mState == "Summon") {
		mpAnimation->SetNewStateOneTime("Spell", 2.0f);
		mCoolSummon = 0.0f;
		mUsedSummon = true;
		mSummonThread = std::thread(&BossBehavior::Summon, this);
		mState = "Idle";
	}
	else if (mState == "Dying") {
		Dying();
	}
}

void BossBehavior::Summonprocess() {

	if (mUsedSummon)
		mSummonThreadWaitTime += Time::GetDeltaTime();

	if (mSummonThreadWaitTime > 0.75f) {
		mSummonenemy->StandBy = true;
		mSummonThread.join();
		mSummonThreadWaitTime = 0.0f;
		mUsedSummon = false;
	}
}

void BossBehavior::Summon() {

	std::uniform_real_distribution<float> rndx(-70, 70);
	float offsetx = rndx(Application::RandomGen);

	while(abs(offsetx) < 20)
		offsetx = rndx(Application::RandomGen);

	mSummonenemy = Application::GetScene()->AddGameObject<Enemy>(ObjectLayer);
	mSummonenemy->StandBy = false;
	mSummonenemy->Name = "Enemy";
	mSummonenemy->Position = Position;
	mSummonenemy->Position.x += offsetx;
	mSummonenemy->Create();
	
}