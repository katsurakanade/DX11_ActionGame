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
#include "Skill_Skyblade.h"

void BossBehavior::Init() {

	EnemyBehavior::Init();

	// ��ԏ�����
	mStatemap[BEHAVIOR_STATE_BOSS::Idle] = "Idle";
	mStatemap[BEHAVIOR_STATE_BOSS::Chase] = "Chase";
	mStatemap[BEHAVIOR_STATE_BOSS::Attack] = "Attack";
	mStatemap[BEHAVIOR_STATE_BOSS::Magic] = "Magic";
	mStatemap[BEHAVIOR_STATE_BOSS::Summon] = "Summon";
	mStatemap[BEHAVIOR_STATE_BOSS::Dying] = "Dying";
	mStart = false;
	// HP������
	mHpInit = 300.0f;
	mHp = mHpInit;
	// �X�L��������
	mUsedSummon = false;
	mCanUseSkill = true;
	mDead = false;
	// �A�j���[�V����������
	mpAnimation->SetCoefficient(1.0f);

	mPlusSpeedChase = 0.05f;
	mMaxSpeedChase = 1.5f;
}

void BossBehavior::Uninit() {
	EnemyBehavior::Uninit();
}

void BossBehavior::Update() {

	EnemyBehavior::Update();

	if (!mStart) {
		if (mLengthToPlayer < 50.0f) {
			mStart = true;
			mpAnimation->SetNewStateOneTime("PowerUp", 2.0f);
			AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::ALIEN_HUMAN), 0, 3.0f);
		}
	}

	if (mStart) {
		// ��������
		Summonprocess();

		// �s������
		ChooseAction();

		// �s��
		RunAction();
	}


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
		ImGui::Text(u8"�N�[���^�C�� %f ", mCoolSkill);
		ImGui::TreePop();
	}
	ImGui::End();
}

void BossBehavior::ChooseAction() {

	// �����Ă���G�̐�
	auto enemyalive = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer).size();
	if (mCanUseSkill) {
		mCoolSkill += Time::GetDeltaTime();
	}

	// �����Ă���
	if (mHp > 0.0f) {

		// ->�U�����
		if (mLengthToPlayer < 20.0f) {
		/*	mState = "Attack";
			mCanUseSkill = false;*/
		}
		// ->�ǐՏ��
		if (mLengthToPlayer >= 20.0f && mLengthToPlayer < 40.0f) {
			/*mState = "Chase";
			mCanUseSkill = false;*/
		}
		// ->�ҋ@���
		else if (mLengthToPlayer > 40.0f) {
			mState = "Idle";
			mCanUseSkill = true;
		}

		// �ҋ@���
		if (mState == "Idle") {

			// �X�L���g��
			if (mCoolSkill >= 5.0f) {
				// ->�������
				if (enemyalive < 4) {
					mState = "Summon";
				}
				// ->���@�U�����
				else {
					mState = "Magic";
				}
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
		if (!mDead)
			AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::ALIEN_DIE), 0, 3.5f);
		mDead = true;
		mState = "Dying";
	}
}

void BossBehavior::RunAction() {

	if (mState == "Idle") {
		if (mpAnimation->GetState() == "Running") {
			mpAnimation->SetNewState("Idle");
		}
	}
	else if (mState == "Chase") {
		LookAt(mpPlayer->Position);
		mpAnimation->SetNewState("Running");
		MoveTo(mpPlayer->Position + D3DXVECTOR3(0,0,5));
		mCoolSkill = 0.0f;
	}
	else if (mState == "Attack") {
		LookAt(mpPlayer->Position);
		mpAnimation->SetNewStateOneTime("Attack", 0.8f);
		mCoolSkill = 0.0f;
	}
	else if (mState == "Magic") {

		mpAnimation->SetNewStateOneTime("Spell2", 2.0f);
		mUsedMagic = true;

		LookAt(mpPlayer->Position);
		AudioListener::Play(Application::GetScene()->GetAsset()->GetSound((int)SOUND_ENUM_GAME::ALIEN_KILLYOU), 0, 2.5f);


		Skill_Skyblade* sk = Application::GetScene()->AddGameObject<Skill_Skyblade>(ObjectLayer);
		sk->Position = mpPlayer->Position + D3DXVECTOR3(0, 1, 0);

		mState = "Idle";
		mCoolSkill = 0.0f;
	}
	else if (mState == "Summon") {

		mpAnimation->SetNewStateOneTime("Spell", 2.0f);
		mUsedSummon = true;
		mSummonThread = std::thread(&BossBehavior::Summon, this);

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
	
		mState = "Idle";
		mCoolSkill = 0.0f;
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