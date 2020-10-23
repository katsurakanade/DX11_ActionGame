#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Player.h"
#include "input.h"
#include "Animation.h"
#include "Particle.h"
#include "Shader.h"
#include "MeshField.h"
#include "Collision.h"
#include "ModelManager.h"
#include "item.h"
#include "Missile.h"
#include <random>

void Player::Init() {

	Name = "Player";
	mCharacterType = 0;

	Position = D3DXVECTOR3(100, 12,55);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

	D3DXQuaternionIdentity(&Quaternion);
	
	AddComponent<BoxCollider>();
	AddComponent<Physical>();

	mpAnination = AddComponent<Animation>();
	mpModel = AddComponent<ModelManager>();

	mpModel->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN));
	mpModel->SetAnimation(mpAnination);

	GetComponent<BoxCollider>()->mPositionOffest = D3DXVECTOR3(0.0f, 4.25f, 0.0f);
	GetComponent<BoxCollider>()->mScaleOffest = D3DXVECTOR3(2.5f, 9.0f, 2.5f);

	Camera* camera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);
	camera->SetFollowTarget(this);

	mHp = mHpInit;

	mpAnination->SetState("Idle");
	mpAnination->SetCoefficient(10.0f);

	for (Component* c : Components) {
		c->SetUsePanel(true);
	}

	mpCamera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);

	Resource::Init();

}

void Player::Unint() {

	Resource::Uninit();
}

void Player::Update() {

	float speed = GetComponent<Physical>()->mSpeed;
	
	// アニメーション更新
	if (mpAnination->GetState() == "Idle" && speed >= 1.5f) {
		mpAnination->SetNewState("Running");
	}
	if (mpAnination->GetState() == "Running" && speed <= 1.0f) {
		mpAnination->SetNewState("Idle");
		mpAnination->SetCoefficient(60.0f);
	}

	// 移動
	Movement(DIK_W, DIK_S, DIK_A, DIK_D);

	// 高さ修正
	MeshField* mf = Application::GetScene()->GetGameObject<MeshField>(ObjectLayer);
	Position.y = mf->GetHeight(Position) + mf->Position.y;

	// スキル
	Skill(DIK_1, DIK_2, DIK_3, DIK_4);

	// キャラ変更
	if (Input::GetKeyTrigger(DIK_N)) {
		if (GetComponent<ModelManager>()->GetModel()  != Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN)) {
			ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			ParitcleSetting* setting = new ParitcleSetting;
			setting->Amount = 3000;
			setting->PostionMinMaxX = D3DXVECTOR2(-5, 5);
			setting->PostionMinMaxY = D3DXVECTOR2(-5, 5);
			setting->SpeedMinMaxX = D3DXVECTOR2(-0.5f, 0.5f);
			setting->SpeedMinMaxY = D3DXVECTOR2(-0.5f, 0.5f);
			setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 1.0f);
			setting->LifeMinMax = D3DXVECTOR2(10.0f, 120.0f);
			setting->Size = 0.5f;
			pc->Create(setting);
			delete setting;

			pc->Position = Position;
			pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::HANE));

			GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN));
			GUI* gui = Application::GetScene()->GetGameObject<GUI>(SpriteLayer);
			gui->SetPlayerIcon(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::CHARACTERICON_0));

			mCharacterType = 0;
		}
	}
	if (Input::GetKeyTrigger(DIK_M)) {

		if (GetComponent<ModelManager>()->GetModel() != Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN2)) {

			ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			ParitcleSetting* setting = new ParitcleSetting;
			setting->Amount = 3000;
			setting->PostionMinMaxX = D3DXVECTOR2(-5, 5);
			setting->PostionMinMaxY = D3DXVECTOR2(-5, 5);
			setting->SpeedMinMaxX = D3DXVECTOR2(-0.5f, 0.5f);
			setting->SpeedMinMaxY = D3DXVECTOR2(-0.5f, 0.5f);
			setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 1.0f);
			setting->LifeMinMax = D3DXVECTOR2(10.0f, 120.0f);
			setting->Size = 0.5f;
			pc->Create(setting);
			delete setting;

			pc->Position = Position;
			pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::HANE));

			GetComponent<ModelManager>()->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::HUMAN2));
			GUI* gui = Application::GetScene()->GetGameObject<GUI>(SpriteLayer);
			gui->SetPlayerIcon(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::CHARACTERICON_1));

			mCharacterType = 1;
		}
		
	}

	// 敵ロック
	if (Input::GetKeyTrigger(DIK_R)) {

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

		if (Input::GetKeyTrigger(DIK_RIGHTARROW) ) {
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
			if (mLockIndex > 0){
				mLockIndex--;
			}
			else if (mLockIndex == 0) {
				mLockIndex = enemys.size() - 1;
			}
			mpCamera->SetLookTarget(enemys[mLockIndex]);
			enemys[mLockIndex]->Is_Lock = true;
		}

	}

	// パーティクル生成（テスト用）
	if (Input::GetKeyTrigger(DIK_C)) {
		ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
		pc->Position = this->Position;
		ParitcleSetting* setting = new ParitcleSetting;
		setting->Amount = 100000;
		setting->PostionMinMaxX = D3DXVECTOR2(-100, 100);
		setting->PostionMinMaxY = D3DXVECTOR2(-100, 100);
		setting->PostionMinMaxZ = D3DXVECTOR2(-100, 100);
		setting->SpeedMinMaxX = D3DXVECTOR2(-1.0f, 1.0f);
		setting->SpeedMinMaxY = D3DXVECTOR2(-1.0f, 1.0f);
		setting->SpeedMinMaxZ = D3DXVECTOR2(-1.0f, 1.0f);
		setting->LifeMinMax = D3DXVECTOR2(60.0f, 300.0f);
		setting->Size = 0.2f;
		pc->Create(setting);
		pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
		delete setting;
	}

	// ForDebug
	SettingPanel();
	
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
	
	Shader::Use(SHADER_TYPE_VSPS::Default);

	mpModel->Render(world);
	
	GetComponent<BoxCollider>()->Render();

}

void Player::SettingPanel() {

	ImGui::Begin(Name.c_str());
	ImGui::SliderFloat3(u8"座標", Position, -1000.0f, 1000.0f, "%.0f", 5.0f);
	ImGui::SliderFloat3(u8"回転", Rotation, -3.14f, 3.14f);
	ImGui::SliderFloat3(u8"スケール", Scale, 0.1f, 10.0f);
	ImGui::End();
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

			if (mpCamera->GetLookTarget()) {
				mpCamera->AddControllerPosition(D3DXVECTOR3(-0.01f, 0, 0));
			}
		}

		else if (Input::GetKeyPress(keykodeR)) {

			Rotation.y = D3DX_PI * -0.25f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}
			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, cosf(-D3DX_PI * 0.75f));

			if (mpCamera->GetLookTarget()) {
				mpCamera->AddControllerPosition(D3DXVECTOR3(0.015f, 0, 0));
			}
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

			if (mpCamera->GetLookTarget()) {
				mpCamera->AddControllerPosition(D3DXVECTOR3(-0.01f, 0, 0));
			}
		}

		else if (Input::GetKeyPress(keykodeR)) {

			Rotation.y = D3DX_PI * -0.75f;

			if (GetComponent<Physical>()->mAcceleration < 1.5f) {
				GetComponent<Physical>()->mAcceleration += 0.1f;
			}
			GetComponent<Physical>()->mSpeed += GetComponent<Physical>()->mAcceleration;
			GetComponent<Physical>()->mVelocity = D3DXVECTOR3(-sinf(-D3DX_PI * 0.75f), 0, -cosf(-D3DX_PI * 0.75f));

			if (mpCamera->GetLookTarget()) {
				mpCamera->AddControllerPosition(D3DXVECTOR3(0.015f, 0, 0));
			}
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

		if (mpCamera->GetLookTarget()) {
			mpCamera->AddControllerPosition(D3DXVECTOR3(-0.01f, 0, 0));
		}
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

		if (mpCamera->GetLookTarget()) {
			mpCamera->AddControllerPosition(D3DXVECTOR3(0.015f, 0, 0));
		}
	}
}

void Player::Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3) {

	if (Input::GetKeyTrigger(keykode_0)) {

		// 全敵取得
		std::vector <Enemy*> es = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

		// 普通攻撃
		if (mCharacterType == 0) {
			mpAnination->SetNewStateOneTime("Attack", 0.7f);

			for (unsigned int i = 0; i < es.size(); i++) {
				if (es[i] != nullptr && es[i]->GetComponent<BoxCollider>()->Collision_Box_Stay(this->GetComponent<BoxCollider>())) {

					ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
					ParitcleSetting* setting = new ParitcleSetting;
					pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
					setting->Amount = 3000;
					setting->SpeedMinMaxX = D3DXVECTOR2(-0.5f, 0.5f);
					setting->SpeedMinMaxY = D3DXVECTOR2(-0.5f, 0.5f);
					setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 1.0f);
					setting->LifeMinMax = D3DXVECTOR2(10.0f, 120.0f);
					setting->Size = 0.1f;
					pc->Create(setting);
					delete setting;
					pc->Position = Position + D3DXVECTOR3(0, 3, 0);

					es[i]->mHp -= 10.0f;
				}
			}
		
		}
		// ファイアボール
		else if (mCharacterType == 1 && mpCamera->GetLookTarget()) {

			mpAnination->SetNewStateOneTime("Mage", 1.0f);

			std::uniform_real_distribution<float> rndx(Position.x - 40, Position.x + 40);
			std::uniform_real_distribution<float> rndy(Position.y + 10, Position.y + 50);
			std::uniform_real_distribution<float> rndz(Position.z - 100, Position.z - 50);

			if (es.size() > 0 && mpAnination->GetState() != "Mage") {
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

	if (Input::GetKeyTrigger(keykode_1)) {
		
	}

	if (Input::GetKeyTrigger(keykode_2)) {

	}

	if (Input::GetKeyTrigger(keykode_3)) {

	}

}