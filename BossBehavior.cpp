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

	// 行動決め
	ChooseAction();

	// 行動
	RunAction();

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

void BossBehavior::ChooseAction() {

	// 生きている敵の数
	auto enemyalive = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer).size();
	if (enemyalive < 4 && mCanUseSkill) {
		mCoolSummon += Time::GetDeltaTime();
	}

	// 生きている
	if (mHp > 0.0f) {

		// 待機状態
		if (mState == "Idle") {
			// ->攻撃状態
			if (mLengthToPlayer < 20.0f) {
				mState = "Attack";
				mCanUseSkill = false;
			}
			// ->召喚状態
			if (mCoolSummon >= 10.0f) {
				mState = "Summon";
			}
			
		}
		// 攻撃状態
		else if (mState == "Attack") {
			// ->待機状態
			if (mLengthToPlayer > 20.0f) {
				mState = "Idle";
				mCanUseSkill = true;
			}
		}

	}
	// 死亡 (-> 死亡状態)
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

		std::uniform_real_distribution<float> rndx(-70, 70);
		float offsetx = rndx(Application::RandomGen);

		while (abs(offsetx) < 20)
			offsetx = rndx(Application::RandomGen);

		mSummonenemyPos = Position;
		mSummonenemyPos.x += offsetx;

		ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
		pc->UseBezier = true;
		pc->Position = mSummonenemyPos;
		ParitcleSetting* setting = &FileManager::ReadParticleJSON("asset\\json_particle\\Test_Particle.json");
		setting->Position = mSummonenemyPos - GetResource()->Position;
		pc->Create(setting);
		pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::BLOOD_PARTICLE));

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

	mSummonenemy = Application::GetScene()->AddGameObject<Enemy>(ObjectLayer);
	mSummonenemy->StandBy = false;
	mSummonenemy->Name = "Enemy";
	mSummonenemy->Position = mSummonenemyPos;
	mSummonenemy->Create();

	auto sprite = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
	sprite->GetComponent<ImageManager>()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::MAGICRING));
	sprite->GetComponent<ImageManager>()->SetBillBoard(false);
	sprite->GetComponent<ImageManager>()->SetAnimationSprite(true);
	sprite->GetComponent<ImageManager>()->SetGUI(false);
	sprite->GetComponent<ImageManager>()->SetHW(1, 1);
	sprite->GetComponent<ImageManager>()->SetLoop(true);
	sprite->GetComponent<ImageManager>()->SetHighBrightness(true);
	sprite->Position = mSummonenemy->Position + D3DXVECTOR3(0,1,0);
	sprite->Rotation = D3DXVECTOR3(1.72f, 0, 0);
	sprite->Scale = D3DXVECTOR3(5, 5, 5);

}