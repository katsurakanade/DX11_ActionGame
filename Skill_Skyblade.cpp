#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Player.h"
#include "Skill_Skyblade.h"
#include "Sprite.h"
#include "Particle.h"
#include "Collision.h"

void Skill_Skyblade::Init() {

	Name = "MagicRing";
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXQuaternionIdentity(&Quaternion);

	// プレイヤー取得
	mpPlayer = Application::GetScene()->GetGameObject<Player>(ObjectLayer);

	// 魔法陣生成
	mMagicRing = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
	mMagicRing->GetComponent<ImageManager>()->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_GAME::MAGICRING));
	mMagicRing->GetComponent<ImageManager>()->SetBillBoard(false);
	mMagicRing->GetComponent<ImageManager>()->SetAnimationSprite(true);
	mMagicRing->GetComponent<ImageManager>()->SetGUI(false);
	mMagicRing->GetComponent<ImageManager>()->SetHW(1, 1);
	mMagicRing->GetComponent<ImageManager>()->SetLoop(true);
	mMagicRing->GetComponent<ImageManager>()->SetHighBrightness(true);
	mMagicRing->Position = mpPlayer->Position + D3DXVECTOR3(0, 1, 0);
	mMagicRing->Rotation = D3DXVECTOR3(1.57f, 0, 0);
	mMagicRing->Scale = D3DXVECTOR3(20, 10, 20);

	mCollider = AddComponent<BoxCollider>();
	mCollider->mPositionOffest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mCollider->mScaleOffestCoff = D3DXVECTOR3(33.0f,10.0f, 15.0f);

	mDamageTimer = 0.0f;

	Resource::Init();
}

void Skill_Skyblade::Uninit() {
	mMagicRing->Destroy();
	if (mEffect) 
		mEffect->Destroy();

	Resource::Uninit();
}

void Skill_Skyblade::Update() {

	mDamageTimer += Time::GetDeltaTime();
	mKillTimer += Time::GetDeltaTime();
	
	if (mDamageTimer >= 2.0f) {
		if (!mEffect) {
			mEffect = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			mEffect->Position = this->Position + D3DXVECTOR3(0, 30, 0);
			ParitcleSetting* setting = &FileManager::ReadParticleJSON("asset\\json_particle\\BossMagic_Particle.json");
			mEffect->Create(setting);
			mEffect->SetTexture(Asset::GetInstance()->GetTexture((int)TEXTURE_ENUM_GAME::SWORD));
		}
		
	}
	if (mDamageTimer >= 2.75f) {
		if (mCollider->Collision_Box_Stay(mpPlayer->GetComponent<BoxCollider>())) {
			mpPlayer->mHp -= 20.0f;
		}
	}

	if (mKillTimer >= 3.5f) {
		Destroy();
	}

	Resource::Update();
}

void Skill_Skyblade::Render() {
	mCollider->Render();
}