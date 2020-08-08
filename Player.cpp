#include "main.h"
#include "Renderer.h"
#include "Player.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Effect.h"
#include "field.h"

void Player::Init() {

	Name = "Player";

	m_Model = Asset::GetAssimpModel(ASSIMP_MODEL_ENUM::BALL);
	
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	D3DXQuaternionIdentity(&Quaternion);	
	m_Model->DisplayConfig = false;

	Application::GetScene()->GetGameObject<Camera>(CameraLayer)->SetFollowTarget(this);

	AddComponent<BoxCollider>();

	Resource::Init();
}

void Player::Uninit() {
	Resource::Uninit();
}

void Player::Update() {

	if (Input::GetKeyPress('W')) {
		Position.z += Speed;
	}

	if (Input::GetKeyPress('S')) {
		Position.z -= Speed;
	}

	if (Input::GetKeyPress('A')) {
		Position.x -= Speed;
	}

	if (Input::GetKeyPress('D')) {
		Position.x += Speed;
	}

	std::vector<Wall*> Walllist = Application::GetScene()->GetGameObjects<Wall>(ObjectLayer);

	for (Wall* trg : Walllist) {

		if (auto p = trg->GetComponent<BoxCollider>()) {
			if (GetComponent<BoxCollider>()->Collision_Box_Stay(p)) {
				Effect* obj = Application::GetScene()->AddGameObject<Effect>(ObjectLayer);
				obj->Position = Position;
				obj->SetHW(8, 6);
			}
		}

	}

	GetComponent<BoxCollider>()->Update(Position, Rotation, Scale);

}
 
void Player::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw(world);
	GetComponent<BoxCollider>()->Render();
}