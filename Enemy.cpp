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
	mpBehavior = AddComponent<EnemyBehavior>();

	mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 4.2f, 0.0f);
	mpCollider->mScaleOffestCoff = D3DXVECTOR3(150.0f, 157.0f, 150.0f);
	mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 3.5f, 0.0f);
	mpCollider->mScaleOffest = D3DXVECTOR3(3.2f, 7.14f, 3.2f);
	mpCollider->SetUsePanel(true);

	mpAnination->SetState("Idle");
	mpAnination->SetUsePanel(true);

	mModel = new AssimpModel(true);
	mModel->Load("asset\\model\\enemy\\Enemy.fbx");
	mModel->LoadAnimation("asset\\animation\\Idle.fbx","Idle");
	mModel->LoadAnimation("asset\\animation\\Running.fbx", "Running");
	mModel->LoadAnimation("asset\\animation\\Attack.fbx", "Attack");
	mModel->LoadAnimation("asset\\animation\\Dying.fbx", "Dying");
	mpModel->SetModel(mModel);

	mpLockImage = Application::GetScene()->AddGameObject<Sprite>(EffectLayer2);
	mpLockImage->Name = "enemy_lock_" + Name;
	mpLockImage->GetImage()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
	mpLockImage->GetImage()->SetAnimationSprite(true);
	mpLockImage->GetImage()->SetBillBoard(true);
	mpLockImage->GetImage()->SetHW(1,1);
	mpLockImage->GetImage()->SetLoop(true);
	mpLockImage->Position = Position;
	mpLockImage->Scale = D3DXVECTOR3(3, 3, 3);
	mpLockImage->SetActive(false);

	mpBehavior->SetUsePanel(true);

	AddGauge();
	Resource::Init();

}

void Enemy::AddGauge() {

	Gauge* gauge = Application::GetScene()->AddGameObject<Gauge>(EffectLayer);
	gauge->SetBillBoard(this);
	gauge->mPositionOffest = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
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
	if (mModel) {
		mModel->Unload();
		delete mModel;
		mModel = nullptr;
	}

	Resource::Uninit();
}

void Enemy::Update() {

	if (mGauge) {
		mGauge->mFillAmount = mpBehavior->mHp / mpBehavior->mHpInit;
	}

	MeshField* mf = Application::GetScene()->GetGameObject<MeshField>(ObjectLayer);
	Position.y = mf->GetHeight(Position) + mf->Position.y;

	mpLockImage->Position = Position + D3DXVECTOR3(0, 5, 3);

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


