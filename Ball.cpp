#include "main.h"
#include "Mathematics.h"
#include "Renderer.h"
#include "Ball.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Wall.h"
#include "Enemy.h"
#include "Effect.h"
#include "Physical.h"
#include "field.h"

void Ball::Init() {

	Name = "Ball";

	mModel = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::BALL);

	Position = D3DXVECTOR3(0, 10, 10);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	
	D3DXQuaternionIdentity(&Quaternion);	

	AddComponent<BoxCollider>();
	AddComponent<Physical>();

	mArrow = Application::GetScene()->AddGameObject<Arrow>(ObjectLayer);
	
	GetComponent<BoxCollider>()->mScaleOffest  = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

	Resource::Init();
}

void Ball::Uninit() {
	mArrow->Uninit();
	Resource::Uninit();
}

void Ball::Update() {

	//ImGui::Begin(Name.c_str());
	//ImGui::Text("%f,%f,%f", Rotation.x, Rotation.y, Rotation.z);
	//ImGui::SetWindowSize(ImVec2(500, 200));
	//float fp[3] = { Rotation.x ,Rotation.y ,Rotation.z };
	//ImGui::SliderFloat3(u8"‰ñ“]", fp, -3.14f, 3.14f);
	//Rotation = D3DXVECTOR3(fp[0], fp[1], fp[2]);
	//ImGui::End();

	{
		if (Input::GetKeyPress('D')) {
			mArrow->RotationAroundXZ(Position, 1.0f);
		}

		if (Input::GetKeyPress('A')) {
			mArrow->RotationAroundXZ(Position, -1.0f);
		}

		if (Input::GetKeyTrigger(VK_SPACE) && mArrow->GetActive()) {
			GetComponent<Physical>()->Start();
			D3DXVECTOR3 dir = mArrow->Position - Position;
			D3DXVECTOR3 dirn;
			D3DXVec3Normalize(&dirn, &dir);
			GetComponent<Physical>()->mVelocity = -dir;
			mArrow->SetActive(false);
			Change = true;
		}

		mArrow->Update();
	}

	if (Change) {
		if (GetComponent<Physical>()->mSpeed == 0.00f) {
			Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
			if (p->mNowController < 1) {
				p->mNowController++;
			}
			else {
				p->mNowController = 0;
			}
			p->SelectBall();
			Change = false;
		}
	}

	ReflectWall();
	ReflectBall();

	Resource::Update();
}
 
void Ball::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mModel->DefaultTexture = false;
	mModel->SelectTextureIndex = TexutreIndex;
	mModel->Draw(world);

	if (mArrow->GetActive()) {
		mArrow->Render();
	}

	GetComponent<BoxCollider>()->Render();
}

void Ball::ReflectWall() {

	std::vector<Wall*> Walllist = Application::GetScene()->GetGameObjects<Wall>(ObjectLayer);

	for (Wall* trg : Walllist) {

		BoxCollider* sbc = GetComponent<BoxCollider>();
		BoxCollider* tbc = trg->GetComponent<BoxCollider>();

		if (sbc->Collision_Box_Enter(tbc)) {

			// Self
			GetComponent<Physical>()->mSpeed -= 0.05f;
			D3DXVECTOR3 moveDir;
			D3DXVec3Normalize(&moveDir, &GetComponent<Physical>()->mVelocity);
			D3DXVECTOR3 r;
			GetReflectVector(&r, moveDir, trg->GetFront());
			GetComponent<Physical>()->mVelocity = r;
			GetComponent<Physical>()->AddForce(this, 1.5);

			// Effect
			Effect* obj = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
			obj->Position = Position;
			obj->SetHW(8, 6);
		}
	}
}

void Ball::ReflectBall() {

	std::vector<Ball*> Balllist = Application::GetScene()->GetGameObjects<Ball>(ObjectLayer);

	for (Ball* trg : Balllist) {

		if (trg->Name != this->Name && !trg->Change) {
			BoxCollider* sbc = GetComponent<BoxCollider>();
			BoxCollider* tbc = trg->GetComponent<BoxCollider>();

			if (sbc->Collision_Box_Enter(tbc)) {

				// Target
				trg->GetComponent<Physical>()->mSpeed = 0.01f;
				D3DXVECTOR3 dir = trg->Position - Position;
				D3DXVECTOR3 dirn;
				D3DXVec3Normalize(&dirn, &dir);
				trg->GetComponent<Physical>()->mVelocity = dir;
			}
		}
	}
}