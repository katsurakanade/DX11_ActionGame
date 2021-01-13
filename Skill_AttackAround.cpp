#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Player.h"
#include "BossBehavior.h"
#include "Skill_AttackAround.h"
#include "Sprite.h"
#include "Particle.h"
#include "Collision.h"

void Skill_AttackAround::Init() {

	Name = "Enemy_AttackAround";
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXQuaternionIdentity(&Quaternion);

	// プレイヤー取得
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);

	// 魔法陣生成
	mMagicRing = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
	mMagicRing->GetImage()->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_GAME::MAGICRING));
	mMagicRing->GetImage()->SetBillBoard(false);
	mMagicRing->GetImage()->SetAnimationSprite(true);
	mMagicRing->GetImage()->SetGUI(false);
	mMagicRing->GetImage()->SetHW(1, 1);
	mMagicRing->GetImage()->SetLoop(true);
	mMagicRing->GetImage()->SetHighBrightness(true);
	mMagicRing->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mMagicRing->Rotation = D3DXVECTOR3(1.57f, 0, 0);
	mMagicRing->Scale = D3DXVECTOR3(40, 40, 40);

	mDamageTimer = 0.0f;

	Resource::Init();
}
void Skill_AttackAround::Uninit() {

	mMagicRing->Destroy();
	if (mEffect)
		mEffect->Destroy();

	Resource::Uninit();
}
void Skill_AttackAround::Update() {

	mMagicRing->Position = Position;

	mDamageTimer += Time::GetDeltaTime();
	mKillTimer += Time::GetDeltaTime();

	if (!mEffect) {
		mEffect = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
		mEffect->UseBezier = true;
		mEffect->Position = Position;
		ParitcleSetting* setting = &FileManager::ReadParticleJSON("asset\\json_particle\\Test_Particle.json");
		setting->Position = Position - (Position + D3DXVECTOR3(0,30,0));
		mEffect->Create(setting);
		mEffect->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_GAME::BLOOD_PARTICLE));
	}

	if (mDamageTimer >= 2.75f) {
		if (mpBossBehavior->GetLengthToPlayer() < 37.0f) {
			mpPlayer->mHp -= 50.0f;
		}
	}

	if (mKillTimer > 3.5f) {
		AudioListener::Play(Asset::GetInstance()->GetSound((int)SOUND_ENUM_GAME::IMPACT_GROUND), 0, 2.5f);
		Destroy();
	}
	Resource::Update();
}

void Skill_AttackAround::Render() {
	mCollider->Render();
}
