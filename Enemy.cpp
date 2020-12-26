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
#include "Behavior.h"
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
	mpBehavior = AddComponent<Behavior>();

	mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 4.2f, 0.0f);
	mpCollider->mScaleOffestCoff = D3DXVECTOR3(52.0f, 157.0f, 60.0f);
	mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 3.5f, 0.0f);
	mpCollider->mScaleOffest = D3DXVECTOR3(3.2f, 7.14f, 3.2f);

	mpAnination->SetState("Idle");
	mpAnination->SetCoefficient(10.0f);
	mpAnination->SetUsePanel(true);

	mpModel->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ENEMY));
	mpModel->SetAnimation(mpAnination);

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


	AddGauge();
	Resource::Init();

}

void Enemy::AddGauge() {

	Gauge* gauge = Application::GetScene()->AddGameObject<Gauge>(EffectLayer);
	gauge->SetBillBoard(this);
	gauge->mPositionOffest = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	mGauge = gauge;

	mHpInit = 50.0f;
	mHp = mHpInit;
	mGauge->mFillAmount = mHp / mHpInit;

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
		mGauge->mFillAmount = mHp / mHpInit;
	}

	if (Input::GetKeyTrigger(DIK_H)) {
		mStart = true;
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

	if (mHp <= 0.0f) {

		Camera* camera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);

		if (camera) {
			camera->SetLookTarget(nullptr);
		}

		Destroy();
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


