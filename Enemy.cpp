#include "main.h"
#include "Renderer.h"
#include "Scene.h"
#include "Application.h"
#include "Enemy.h"
#include "Ball.h"

void Enemy::Init() {

	Name = "Enemy";

	mModel = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::ENEMY);

	Position = D3DXVECTOR3(0, 10, 0);
	Rotation = D3DXVECTOR3(1.72f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	D3DXQuaternionIdentity(&Quaternion);

	AddComponent<Physical>();
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->mPositionOffest = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	GetComponent<BoxCollider>()->mScaleOffest = D3DXVECTOR3(7.2f, 7.2f, 7.2f);

	Resource::Init();
}

void Enemy::Unint() {
	Resource::Uninit();
}

void Enemy::Update() {

	//{
	//	ImGui::Begin(u8"Enemy");
	//	ImGui::Text(u8"Hp %f", hp);
	//	ImGui::End();
	//}

	std::vector<Ball*> PlayerList = Application::GetScene()->GetGameObjects<Ball>(ObjectLayer);

	for (Ball* trg : PlayerList) {

		BoxCollider* sbc = GetComponent<BoxCollider>();
		BoxCollider* tbc = trg->GetComponent<BoxCollider>();

		if (sbc->Collision_Box_Enter(tbc)) {

			// Self
			GetComponent<Physical>()->mSpeed = 0.01f;
			D3DXVECTOR3 dir = trg->Position - Position;
			D3DXVECTOR3 dirn;
			D3DXVec3Normalize(&dirn, &dir);
			GetComponent<Physical>()->mVelocity = dir;

			// Target
			trg->GetComponent<Physical>()->SpeedDown(0.0015f);

			// Effect
			Effect* obj = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
			obj->Position = Position;
			obj->SetHW(8, 6);
			hp -= 1.0f;
		}
	}

	if (hp <= 0) {
		Destroy();
	}

	Resource::Update();
}

void Enemy::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mModel->Draw(world);

	GetComponent<BoxCollider>()->Render();
}
