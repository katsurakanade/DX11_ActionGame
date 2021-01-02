#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Player.h"
#include "input.h"
#include "Particle.h"
#include "Shader.h"
#include "MeshField.h"
#include "PlayerBehavior.h"
#include "Collision.h"
#include "Animation.h"
#include "ModelManager.h"
#include "item.h"
#include <random>

void Player::Init() {

	// 基本情報初期化
	Name = "Player";
	Position = D3DXVECTOR3(100, 12,55);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	D3DXQuaternionIdentity(&Quaternion);
	mHp = mHpInit;
	
	// コンポーネント追加
	mpCollider = AddComponent<BoxCollider>();
	mpPhysical = AddComponent<Physical>();
	mpAnination = AddComponent<Animation>();
	mpModel = AddComponent<ModelManager>();
	mpPlayerBehavior = AddComponent<PlayerBehavior>();

	// モデルコンポーネント初期化
	mpModel->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN));

	// 当たり判定コンポーネント初期化
	mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 4.2f, 0.0f);
	mpCollider->mScaleOffestCoff = D3DXVECTOR3(150.0f, 157.0f, 150.0f);
	mpCollider->SetUsePanel(true);

	// アニメーションコンポーネント初期化
	mpAnination->SetState("Idle");

	// カメラ調整
	mpCamera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);
	mpCamera->SetFollowTarget(this);

	// パネル表示
	for (Component* c : Components) {
		c->SetUsePanel(true);
	}
	mpModel->GetModel()->DisplayConfig = true;

	Resource::Init();

}

void Player::Unint() {
	Resource::Uninit();
}

void Player::Update() {
	
	// アニメーション更新
	float speed = mpPhysical->mSpeed;
	if (mpAnination->GetState() == "Idle" && speed >= 1.5f) {
		mpAnination->SetNewState("Running");
	}
	if (mpAnination->GetState() == "Running" && speed <= 1.0f) {
		mpAnination->SetNewState("Idle");
	}

	// 高さ修正
	MeshField* mf = Application::GetScene()->GetGameObject<MeshField>(ObjectLayer);
	Position.y = mf->GetHeight(Position) + mf->Position.y; 

	// ForDebug
	SettingPanel();

	Resource::Update();

}

void Player::Render() {

	D3DXMATRIX world = MakeWorldMatrix();
	Renderer::SetWorldMatrix(&world);
	Shader::Use(SHADER_TYPE_VSPS::Default);

	mpModel->Render(world);
	mpCollider->Render();

}

void Player::SettingPanel() {

	ImGui::Begin(Name.c_str());
	ImGui::SliderFloat3(u8"座標", Position, -1000.0f, 1000.0f, "%.0f", 5.0f);
	ImGui::SliderFloat3(u8"回転", Rotation, -3.14f, 3.14f);
	ImGui::SliderFloat3(u8"スケール", Scale, 0.1f, 10.0f);
	ImGui::End();
}


