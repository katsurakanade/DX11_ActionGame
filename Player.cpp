#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Player.h"
#include "input.h"
#include "Mathematics.h"

void Player::Init() {

	Name = "Player";

	mModel = Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN);

	Position = D3DXVECTOR3(0, 12, 20);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

	D3DXQuaternionIdentity(&Quaternion);

	AddComponent<BoxCollider>();
	AddComponent<Physical>();

	GetComponent<BoxCollider>()->mPositionOffest = D3DXVECTOR3(0.0f, 4.25f, 0.0f);
	GetComponent<BoxCollider>()->mScaleOffest = D3DXVECTOR3(2.5f, 9.0f, 2.5f);

	Camera* camera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);
	camera->SetFollowTarget(this);

	for (Component* c : Components) {
		c->SetUsePanel(true);
	}

	Resource::Init();

	mHp = mHpInit;
}

void Player::Unint() {
	Resource::Uninit();
}

void Player::Update() {


	if (GetComponent<Physical>()->mSpeed >= 1.5f) {
		mFrame++;
		mModel->Update(mFrame);
	}

	SettingPanel();

	// ジャンプ
	//Jump(DIK_SPACE);

	// 移動
	Movement(DIK_W, DIK_S, DIK_A, DIK_D);

	// スキル
	Skill(DIK_Q, DIK_W, DIK_E, DIK_R);

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
	
	mModel->DisplayConfig = true;
	mModel->Draw(world);
	
	GetComponent<BoxCollider>()->Render();
}

void Player::SettingPanel() {

	ImGui::Begin(Name.c_str());
	ImGui::SliderFloat3(u8"座標", Position, -1000.0f, 1000.0f, "%.0f", 5.0f);
	ImGui::SliderFloat3(u8"回転", Rotation, -3.14f, 3.14f);
	ImGui::SliderFloat3(u8"スケール", Scale, 0.1f, 10.0f);
	ImGui::Text(u8"ジャンプ可能 %d ", mCanJump);
	ImGui::Text(u8"ジャンプ速度 %f", mJumpVel);
	ImGui::End();
}

void Player::Jump(BYTE keykode) {

	if (Input::GetKeyTrigger(keykode)) {
		mCanJump = false;
		mJumpVel = 0;
	}

	if (mCanJump == false) {
		Position.y = 50 * sin(2.0f * 3.14f / 40.0f * mJumpTime);
		mJumpTime++;
	}

	/*float speed = GetComponent<Physical>()->mSpeed;

	if (speed <= 0.1f) {
		GetComponent<Physical>()->AddForce(D3DXVECTOR3(0, 15.0f, 0) * mJumpVel);
	}

	else {
		D3DXVECTOR3 forward;
		D3DXVec3Normalize(&forward, &-GetForward());
		D3DXVECTOR3 dir = (forward)+D3DXVECTOR3(0, -1.0f, 0);
		D3DXVECTOR3 r;
		GetReflectVector(&r, dir, D3DXVECTOR3(0, 15.0f, 0));
		r.z = 0;
		GetComponent<Physical>()->AddForce(r * speed * mJumpVel);
	}*/

	if (Position.y > 1) {
		mCanJump = true;
		mJumpVel = 0;
		mJumpTime = 0;
	}

}

void Player::Movement(BYTE keykodeF , BYTE keykodeB ,BYTE keykodeR, BYTE keykodeL) {

	if (Input::GetKeyPress(keykodeF)) {

		if (Input::GetKeyPress(keykodeL)) {

			Rotation.y = D3DX_PI * 0.25f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}

			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) , 0, cosf(-D3DX_PI * 0.75f));
		}

		else if (Input::GetKeyPress(keykodeR)) {

			Rotation.y = D3DX_PI * -0.25f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}
			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));
		}

		else {

			Rotation.y = 0.0f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}
			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(0, 0, -1.0f);
		}
	}

	else if (Input::GetKeyPress(keykodeB)) {

		if (Input::GetKeyPress(keykodeL)) {

			Rotation.y = D3DX_PI * 0.75f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}

			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));
		}

		else if (Input::GetKeyPress(keykodeR)) {

			Rotation.y = D3DX_PI * -0.75f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}
			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));
		}


		else {

			Rotation.y = D3DX_PI;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}
			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(0, 0, 1.0);
		}
	}

	else if (Input::GetKeyPress(keykodeL)) {

		if (Rotation.y != 1.72f) {
			Rotation = D3DXVECTOR3(0.0f, 1.72f, 0.0f);
		}

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}
		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-1.0f, 0, 0);
	}

	else if (Input::GetKeyPress(keykodeR)) {

		if (Rotation.y != -1.72f) {
			Rotation = D3DXVECTOR3(0.0f, -1.72f, 0.0f);
		}

		if (GetComponent<Physical>()->mAcceleration < 1.5f) {
			GetComponent<Physical>()->mAcceleration += 0.1f;
		}
		GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
		GetComponent<Physical>()->mVelocity = D3DXVECTOR3(1.0f, 0, 0);
	}
}

void Player::Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3) {

	if (Input::GetKeyTrigger(keykode_0)) {
	}

	if (Input::GetKeyTrigger(keykode_1)) {

	}

	if (Input::GetKeyTrigger(keykode_2)) {

	}

	if (Input::GetKeyTrigger(keykode_3)) {

	}

}