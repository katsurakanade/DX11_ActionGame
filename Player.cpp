#include "main.h"
#include "Mathematics.h"
#include "Renderer.h"
#include "Player.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Effect.h"
#include "Physical.h"
#include "field.h"

void Player::Init() {

	Name = "Player";

	mModel = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::BALL);

	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	D3DXQuaternionIdentity(&Quaternion);	

	AddComponent<BoxCollider>();
	AddComponent<Physical>();

	Resource::Init();
}

void Player::Uninit() {
	Resource::Uninit();
}

void Player::Update() {

	if (Input::GetKeyTrigger(VK_SPACE)) {
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-2, 1,1) * mSpeed;
	}

	Reflect();

	Resource::Update();
}
 
void Player::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mModel->DefaultTexture = false;
	mModel->Draw(world);
	GetComponent<BoxCollider>()->Render();
}

void Player::Reflect() {

	std::vector<Wall*> Walllist = Application::GetScene()->GetGameObjects<Wall>(ObjectLayer);

	for (Wall* trg : Walllist) {

		BoxCollider* sbc = GetComponent<BoxCollider>();
		BoxCollider* tbc = trg->GetComponent<BoxCollider>();

		if (sbc->Collision_Box_Enter(tbc)) {

			D3DXVECTOR3 moveDir;
			D3DXVec3Normalize(&moveDir, &GetComponent<Physical>()->mVelocity);
			D3DXVECTOR3 r;
			GetReflectVector(&r, moveDir, trg->GetFront());
			GetComponent<Physical>()->mVelocity = r * mSpeed;
			GetComponent<Physical>()->AddForce(this, 1);

			Effect* obj = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
			obj->Position = Position;
			obj->SetHW(8, 6);
		}
	}
}

void Player::SetTexture(int index) {
	mModel->PushTextureSelect(index);
}