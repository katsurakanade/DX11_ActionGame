#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "input.h"
#include "Time.h"
#include "Animation.h"
#include "Physical.h"
#include "Collision.h"
#include "ModelManager.h"
#include "Resource.h"
#include "Particle.h"
#include "Missile.h"
#include "PlayerBehavior.h"

void PlayerBehavior::Init() {

	mpPhysical = GetResource()->GetComponent<Physical>();
	mpAnimation = GetResource()->GetComponent<Animation>();
	mpCollider = GetResource()->GetComponent<BoxCollider>();
	mpModelManager = GetResource()->GetComponent<ModelManager>();

	mpCamera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);
	mpCamera->SetFollowTarget(GetResource());

}

void PlayerBehavior::Uninit() {

}

void PlayerBehavior::Update(){

	Position = GetResource()->Position;

	// 移動
	Movement(DIK_W, DIK_S, DIK_D, DIK_A);
	// スキル
	Skill(DIK_1, DIK_2, DIK_3, DIK_4);
	// キャラクター切替
	SwitchCharacter(DIK_N,DIK_M);
	// 目標ロック
	LockTarget(DIK_R);
}

void PlayerBehavior::FixedUpdate() {
	Component::FixedUpdate();
}

void PlayerBehavior::DataPanel() {

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"行為")) {
		ImGui::Text("CharacterType : %d", mCharacterType);
		ImGui::Text("LockIndex : %d", mLockIndex);
		ImGui::TreePop();
	}
	ImGui::End();
}

void PlayerBehavior::Movement(BYTE keycodeF, BYTE keycodeB, BYTE keycodeR, BYTE keycodeL) {

	// ForWard
	if (Input::GetKeyPress(keycodeF)) {

		if (Input::GetKeyPress(keycodeL)) {

			GetResource()->Rotation.y = D3DX_PI * -0.25f;

			if (mpPhysical->mAcceleration < 1.5f) {
				mpPhysical->mAcceleration += 0.1f;
			}

			mpPhysical->mSpeed += mpPhysical->mAcceleration;
			mpPhysical->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));

			if (mpCamera->GetLookTarget()) {
				mpCamera->AddControllerPosition(D3DXVECTOR3(0.015f, 0, 0));
			}
		}

		else if (Input::GetKeyPress(keycodeR)) {

			GetResource()->Rotation.y = D3DX_PI * 0.25f;

			if (GetResource()->Position.x > -95.0f) {
				if (mpPhysical->mAcceleration < 1.5f) {
					mpPhysical->mAcceleration += 0.1f;
				}
				mpPhysical->mSpeed += mpPhysical->mAcceleration;
				mpPhysical->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));
			}

			if (mpCamera->GetLookTarget()) {
				mpCamera->AddControllerPosition(D3DXVECTOR3(-0.01f, 0, 0));
			}
		}

		else {

			GetResource()->Rotation.y = 0.0f;

			if (mpPhysical->mAcceleration < 1.5f) {
				mpPhysical->mAcceleration += 0.1f;
			}
			mpPhysical->mSpeed += mpPhysical->mAcceleration;
			mpPhysical->mVelocity = D3DXVECTOR3(0, 0, -1.0f);
		}

	}

	// Back
	else if (Input::GetKeyPress(keycodeB)) {

		if (Input::GetKeyPress(keycodeL)) {
			GetResource()->Rotation.y = D3DX_PI * -0.75f;
			if (GetResource()->Position.z < 95.0f) {
				if (mpPhysical->mAcceleration < 1.5f) {
					mpPhysical->mAcceleration += 0.1f;
				}

				mpPhysical->mSpeed += mpPhysical->mAcceleration;
				mpPhysical->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));

				if (mpCamera->GetLookTarget()) {
					mpCamera->AddControllerPosition(D3DXVECTOR3(-0.01f, 0, 0));
				}
			}
		}

		else if (Input::GetKeyPress(keycodeR)) {

			GetResource()->Rotation.y = D3DX_PI * 0.75f;

			if (GetResource()->Position.z < 95.0f && GetResource()->Position.x > -95.0f) {
				if (mpPhysical->mAcceleration < 1.5f) {
					mpPhysical->mAcceleration += 0.1f;
				}
				mpPhysical->mSpeed += mpPhysical->mAcceleration;
				mpPhysical->mVelocity = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));

				if (mpCamera->GetLookTarget()) {
					mpCamera->AddControllerPosition(D3DXVECTOR3(0.015f, 0, 0));
				}
			}
		}

		else {

			GetResource()->Rotation.y = D3DX_PI;

			if (GetResource()->Position.z < 95.0f) {
				if (mpPhysical->mAcceleration < 1.5f) {
					mpPhysical->mAcceleration += 0.1f;
				}
				mpPhysical->mSpeed += mpPhysical->mAcceleration;
				mpPhysical->mVelocity = D3DXVECTOR3(0, 0, 1.0);
			}
		}

	}

	// Left
	else if (Input::GetKeyPress(keycodeL)) {

		if (GetResource()->Rotation.y != -1.72f) {
			GetResource()->Rotation = D3DXVECTOR3(0.0f, -1.72f, 0.0f);
		}

		if (mpPhysical->mAcceleration < 1.5f) {
			mpPhysical->mAcceleration += 0.1f;
		}
		mpPhysical->mSpeed += mpPhysical->mAcceleration;
		mpPhysical->mVelocity = D3DXVECTOR3(1.0f, 0, 0);

		if (mpCamera->GetLookTarget()) {
			mpCamera->AddControllerPosition(D3DXVECTOR3(0.015f, 0, 0));
		}
	}

	// Right
	else if (Input::GetKeyPress(keycodeR)) {

		if (GetResource()->Rotation.y != 1.72f) {
			GetResource()->Rotation = D3DXVECTOR3(0.0f, 1.72f, 0.0f);
		}

		if (GetResource()->Position.x > -95.0f) {
			if (mpPhysical->mAcceleration < 1.5f) {
				mpPhysical->mAcceleration += 0.1f;
			}
			mpPhysical->mSpeed += mpPhysical->mAcceleration;
			mpPhysical->mVelocity = D3DXVECTOR3(-1.0f, 0, 0);
		}

		if (mpCamera->GetLookTarget()) {
			mpCamera->AddControllerPosition(D3DXVECTOR3(-0.01f, 0, 0));
		}
	}

}

void PlayerBehavior::Skill(BYTE keycode_0, BYTE keycode_1, BYTE keycode_2, BYTE keycode_3) {

	if (Input::GetKeyTrigger(keycode_0)) {

		// 全敵取得
		std::vector <Enemy*> es = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

		// 普通攻撃
		if (mCharacterType == 0) {
			mpAnimation->SetNewStateOneTime("Attack", 0.7f);

			for (unsigned int i = 0; i < es.size(); i++) {
				if (es[i] != nullptr && es[i]->GetComponent<BoxCollider>()->Collision_Box_Stay(mpCollider)) {
					ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
					ParitcleSetting* setting = new ParitcleSetting;
					pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
					setting->Amount = 30000;
					setting->SpeedMinMaxX = D3DXVECTOR2(-35.0f, 35.0f);
					setting->SpeedMinMaxY = D3DXVECTOR2(-35.0f, 35.0f);
					setting->SpeedMinMaxZ = D3DXVECTOR2(-50.0f, 50.0f);
					setting->LifeMinMax = D3DXVECTOR2(1.0f, 300.0f);
					setting->Size = 0.1f;
					setting->PolarCoordinates = true;
					pc->Create(setting);
					delete setting;
					pc->Position = Position + D3DXVECTOR3(0, 3, 0);

					es[i]->mHp -= 10.0f;
				}
			}

		}
		// ファイアボール
		else if (mCharacterType == 1 && mpCamera->GetLookTarget()) {

			mpAnimation->SetNewStateOneTime("Mage", 1.0f);

			std::uniform_real_distribution<float> rndx(Position.x - 40, Position.x + 40);
			std::uniform_real_distribution<float> rndy(Position.y + 10, Position.y + 50);
			std::uniform_real_distribution<float> rndz(Position.z - 100, Position.z - 50);

			if (es.size() > 0 && mpAnimation->GetState() != "Mage") {
				Missile* ms = Application::GetScene()->AddGameObject<Missile>(EffectLayer);
				ms->mTargetIndex = mLockIndex;
				ms->Position = Position;
				ms->p0 = ms->Position;
				D3DXVECTOR3 mid = D3DXVECTOR3(rndx(Application::RandomGen), rndy(Application::RandomGen), rndz(Application::RandomGen));
				ms->p1 = mid;
				ms->p2 = es[mLockIndex]->Position;
			}

		}
	}

	if (Input::GetKeyTrigger(keycode_1)) {

	}

	if (Input::GetKeyTrigger(keycode_2)) {

	}

	if (Input::GetKeyTrigger(keycode_3)) {

	}

}

void PlayerBehavior::SwitchCharacter(BYTE keycode_prev ,BYTE keycode_next) {

	if (Input::GetKeyTrigger(keycode_prev)) {
		if (mpModelManager->GetModel() != Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN)) {
			ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			ParitcleSetting* setting = new ParitcleSetting;
			setting->Amount = 3000;
			setting->PostionMinMaxX = D3DXVECTOR2(-5, 5);
			setting->PostionMinMaxY = D3DXVECTOR2(-5, 5);
			setting->SpeedMinMaxX = D3DXVECTOR2(-50.0f, 50.0f);
			setting->SpeedMinMaxY = D3DXVECTOR2(-50.0f, 50.0f);
			setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 10.0f);
			setting->LifeMinMax = D3DXVECTOR2(10.0f, 120.0f);
			setting->Size = 0.2f;
			setting->PolarCoordinates = true;
			pc->Create(setting);
			delete setting;

			pc->Position = Position;
			pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::HANE));

			mpModelManager->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN));
			GUI* gui = Application::GetScene()->GetGameObject<GUI>(SpriteLayer);
			gui->SetPlayerIcon(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::CHARACTERICON_0));

			mCharacterType = 0;
		}
	}
	if (Input::GetKeyTrigger(keycode_next)) {

		if (mpModelManager->GetModel() != Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN2)) {

			ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			ParitcleSetting* setting = new ParitcleSetting;
			setting->Amount = 3000;
			setting->PostionMinMaxX = D3DXVECTOR2(-5, 5);
			setting->PostionMinMaxY = D3DXVECTOR2(-5, 5);
			setting->SpeedMinMaxX = D3DXVECTOR2(-50.0f, 50.0f);
			setting->SpeedMinMaxY = D3DXVECTOR2(-50.0f, 50.0f);
			setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 10.0f);
			setting->LifeMinMax = D3DXVECTOR2(10.0f, 120.0f);
			setting->Size = 0.2f;
			setting->PolarCoordinates = true;
			pc->Create(setting);
			delete setting;

			pc->Position = Position;
			pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::HANE));

			mpModelManager->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN2));
			GUI* gui = Application::GetScene()->GetGameObject<GUI>(SpriteLayer);
			gui->SetPlayerIcon(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::CHARACTERICON_1));

			mCharacterType = 1;
		}

	}
}

void PlayerBehavior::LockTarget(BYTE keycode_lock) {
	if (Input::GetKeyTrigger(keycode_lock)) {

		std::vector <Enemy*> enemys = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

		if (enemys.size() > 0) {
			if (!mpCamera->GetLookTarget()) {
				if (enemys.size() == 1) {
					mLockIndex = 0;
				}
				mpCamera->SetLookTarget(enemys[mLockIndex]);
				mpCamera->SetFollowPostionOffset(D3DXVECTOR3(0, 3, 20));
				enemys[mLockIndex]->Is_Lock = true;
			}
			else {
				mpCamera->SetLookTarget(nullptr);
				enemys[mLockIndex]->Is_Lock = false;
				mpCamera->SetFollowPostionOffset(D3DXVECTOR3(0, 3, 10));
				mpCamera->SetControllerPosition(D3DXVECTOR3(0, 0, 0));
			}
		}

	}
	if (mpCamera->GetLookTarget()) {
		std::vector <Enemy*> enemys = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

		if (Input::GetKeyTrigger(DIK_RIGHTARROW)) {
			enemys[mLockIndex]->Is_Lock = false;
			mpCamera->SetLookTarget(nullptr);
			if (mLockIndex < enemys.size() - 1) {
				mLockIndex++;
			}
			else if (mLockIndex == enemys.size() - 1) {
				mLockIndex = 0;
			}
			mpCamera->SetLookTarget(enemys[mLockIndex]);
			enemys[mLockIndex]->Is_Lock = true;
		}

		else if (Input::GetKeyTrigger(DIK_LEFTARROW)) {
			enemys[mLockIndex]->Is_Lock = false;
			mpCamera->SetLookTarget(nullptr);
			if (mLockIndex > 0) {
				mLockIndex--;
			}
			else if (mLockIndex == 0) {
				mLockIndex = enemys.size() - 1;
			}
			mpCamera->SetLookTarget(enemys[mLockIndex]);
			enemys[mLockIndex]->Is_Lock = true;
		}

	}
}