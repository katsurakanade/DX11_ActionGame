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
#include "Collision.h"


void BossBehavior::Init() {

	EnemyBehavior::Init();

	// 状態初期化
	mStatemap[BEHAVIOR_STATE_BOSS::Idle] = "Idle";
	mStatemap[BEHAVIOR_STATE_BOSS::Chase] = "Chase";
	mStatemap[BEHAVIOR_STATE_BOSS::Attack] = "Attack";
	mStatemap[BEHAVIOR_STATE_BOSS::Magic] = "Magic";
	mStatemap[BEHAVIOR_STATE_BOSS::Summon] = "Summon";
	mStatemap[BEHAVIOR_STATE_BOSS::Dying] = "Dying";
	mStart = false;
	// HP初期化
	mHpInit = 300.0f;
	mHp = mHpInit;
	// スキル初期化
	mCoolSummon = 0.0f;
	mUsedSummon = false;
	mCanUseSkill = true;
	mDead = false;
	// アニメーション初期化
	mpAnimation->SetCoefficient(1.0f);
}

void BossBehavior::Uninit() {
	EnemyBehavior::Uninit();
}

void BossBehavior::Update() {

	EnemyBehavior::Update();

	if (!mStart) {
		if (mLengthToPlayer < 50.0f) {
			mStart = true;
			AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::ALIEN_HUMAN), 0, 3.0f);
		}
	}

	if (mStart) {
		// 召喚処理
		Summonprocess();

		// 行動決め
		ChooseAction();

		// 行動
		RunAction();
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
		ImGui::Text(u8"魔法クールタイム %f ", mCoolMagic);
		ImGui::TreePop();
	}
	ImGui::End();
}

void BossBehavior::ChooseAction() {

	// 生きている敵の数
	auto enemyalive = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer).size();
	if (enemyalive < 8 && mCanUseSkill) {
		mCoolSummon += Time::GetDeltaTime();
	}

	mCoolMagic += Time::GetDeltaTime();

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

			if (mCoolMagic >= 15.0f) {
				mState = "Magic";
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
		if (!mDead)
			AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::ALIEN_DIE), 0, 3.5f);
		mDead = true;
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
	else if (mState == "Magic") {

		AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::ALIEN_KILLYOU), 0, 2.5f);

		mMagicSprite = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
		mMagicSprite->GetComponent<ImageManager>()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::MAGICRING));
		mMagicSprite->GetComponent<ImageManager>()->SetBillBoard(false);
		mMagicSprite->GetComponent<ImageManager>()->SetAnimationSprite(true);
		mMagicSprite->GetComponent<ImageManager>()->SetGUI(false);
		mMagicSprite->GetComponent<ImageManager>()->SetHW(1, 1);
		mMagicSprite->GetComponent<ImageManager>()->SetLoop(true);
		mMagicSprite->GetComponent<ImageManager>()->SetHighBrightness(true);
		mMagicSprite->Position = mpPlayer->Position + D3DXVECTOR3(0,1,0);
		mMagicSprite->Rotation = D3DXVECTOR3(1.57f, 0, 0);
		mMagicSprite->Scale = D3DXVECTOR3(20, 10, 20);

		ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
		pc->Position = mpPlayer->Position + D3DXVECTOR3(0,30,0);
		ParitcleSetting* setting = &FileManager::ReadParticleJSON("asset\\json_particle\\BossMagic_Particle.json");
		pc->Create(setting);
		pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::SWORD));

		mpAnimation->SetNewStateOneTime("Spell", 2.0f);
		mCoolMagic = 0.0f;
		mUsedMagic = true;
		mState = "Idle";

	}
	else if (mState == "Summon") {

		AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::PHRASE), 0, 2.0f);

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

	if (mSummonThreadWaitTime > 2.5f) {
		mSummonenemy->StandBy = true;
		mSummonThread.join();
		mSummonThreadWaitTime = 0.0f;
		mUsedSummon = false;
		mSummonSprite->Destroy();
	}
}

void BossBehavior::Summon() {

	mSummonenemy = Application::GetScene()->AddGameObject<Enemy>(ObjectLayer);
	mSummonenemy->StandBy = false;
	mSummonenemy->Name = "Enemy";
	mSummonenemy->Position = mSummonenemyPos;
	mSummonenemy->Create();

	mSummonSprite = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
	mSummonSprite->GetComponent<ImageManager>()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::MAGICRING));
	mSummonSprite->GetComponent<ImageManager>()->SetBillBoard(false);
	mSummonSprite->GetComponent<ImageManager>()->SetAnimationSprite(true);
	mSummonSprite->GetComponent<ImageManager>()->SetGUI(false);
	mSummonSprite->GetComponent<ImageManager>()->SetHW(1, 1);
	mSummonSprite->GetComponent<ImageManager>()->SetLoop(true);
	mSummonSprite->GetComponent<ImageManager>()->SetHighBrightness(true);
	mSummonSprite->Position = mSummonenemy->Position + D3DXVECTOR3(0,1,0);
	mSummonSprite->Rotation = D3DXVECTOR3(1.57f, 0, 0);
	mSummonSprite->Scale = D3DXVECTOR3(5, 5, 5);

}