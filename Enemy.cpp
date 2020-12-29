#include "main.h"
#include "Renderer.h"
#include "Scene.h"
#include "Application.h"
#include "Enemy.h"
#include "Player.h"
#include "Physical.h"
#include "Animation.h"
#include "input.h"
#include "Shader.h"
#include "Collision.h"
#include "MeshField.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "EnemyBehavior.h"
#include <random>

void Enemy::Init() {

	Name = "Enemy";

	Position = D3DXVECTOR3(0, 12, -20);
	Rotation = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	D3DXQuaternionIdentity(&Quaternion);

	mpPhysical = AddComponent<Physical>();
	mpCollider = AddComponent<BoxCollider>();
	mpAnination = AddComponent<Animation>();
	mpModel = AddComponent<ModelManager>();

	Resource::Init();

}

void Enemy::Create() {

	if (Name == "Boss") {
		mpBehavior = AddComponent<EnemyBehavior>();
		mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 6.5f, 0.0f);
		mpCollider->mScaleOffestCoff = D3DXVECTOR3(200.0f, 157.0f, 200.0f);
		mpCollider->mScaleOffest = D3DXVECTOR3(3.2f, 7.14f, 3.2f);
		mpModel->LoadModelWithAnimation("asset\\model\\enemy\\Boss.fbx");
		Scale = D3DXVECTOR3(0.08f, 0.08f, 0.08f);
		AddGauge(D3DXVECTOR3(0,15,0));
	}
	else {
		mpBehavior = AddComponent<EnemyBehavior>();
		mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 4.2f, 0.0f);
		mpCollider->mScaleOffestCoff = D3DXVECTOR3(150.0f, 157.0f, 150.0f);
		mpCollider->mScaleOffest = D3DXVECTOR3(3.2f, 7.14f, 3.2f);
		mpModel->LoadModelWithAnimation("asset\\model\\enemy\\Enemy.fbx");
		AddGauge(D3DXVECTOR3(0, 10, 0));
	}

	mpLockImage = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
	mpLockImage->Name = "enemy_lock_" + Name;
	mpLockImage->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
	mpLockImage->GetImage()->SetAnimationSprite(true);
	mpLockImage->GetImage()->SetBillBoard(true);
	mpLockImage->GetImage()->SetHW(1, 1);
	mpLockImage->GetImage()->SetLoop(true);
	mpLockImage->Scale = D3DXVECTOR3(1,1,1);
	mpLockImage->SetActive(false);

	// アニメーション設定
	mpAnination->SetState("Idle");

	// パネル表示
	mpCollider->SetUsePanel(true);
	mpAnination->SetUsePanel(true);
	mpBehavior->SetUsePanel(true);


}

void Enemy::AddGauge(D3DXVECTOR3 offset) {

	Gauge* gauge = Application::GetScene()->AddGameObject<Gauge>(EffectLayer);
	gauge->SetBillBoard(this);
	gauge->mPositionOffest = offset;
	mGauge = gauge;

	mGauge->mFillAmount = mpBehavior->mHp / mpBehavior->mHpInit;

}

void Enemy::Uninit() {

	if (mGauge) {
		mGauge->Destroy();
	}
	if (mpLockImage) {
		mpLockImage->Destroy();
	}
	

	Resource::Uninit();
}

void Enemy::Update() {

	if (mGauge) {
		mGauge->mFillAmount = mpBehavior->mHp / mpBehavior->mHpInit;
	}

	MeshField* mf = Application::GetScene()->GetGameObject<MeshField>(ObjectLayer);
	Position.y = mf->GetHeight(Position) + mf->Position.y;

	mpLockImage->Position = Position + D3DXVECTOR3(0, 10, 4);

	if (Is_Lock) {
		mpLockImage->SetActive(true);
	}
	else if (!Is_Lock) {
		mpLockImage->SetActive(false);
	}

	if (mpBehavior->mHp <= 0.0f) {
		mpLockImage->SetActive(false);
	}

	Resource::Update();
}

void Enemy::Render() {


	/*mGauge->Hide(true);
	if (!Application::GetScene()->GetMainCamera()->CheckInView(Position)) {
		mGauge->Hide(true);
		return;
	}*/
	
	D3DXMATRIX world = MakeWorldMatrix();
	Renderer::SetWorldMatrix(&world);
	Shader::Use(SHADER_TYPE_VSPS::Default);
	mGauge->Hide(false);
	mpModel->Render(world);
	mpCollider->Render();

}


