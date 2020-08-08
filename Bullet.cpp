#include "main.h"
#include "Renderer.h"
#include "Bullet.h"
#include "Effect.h"
#include "Application.h"
#include "Scene.h"

void Bullet::Init() {

	Name = "Bullet";

	//m_Model = Asset::GetModel(MODEL_ENUM::BALL);

	Position = D3DXVECTOR3(0, 0, 0);
	Rotation = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	
}

void Bullet::Uninit() {

}

void Bullet::Update() {
	
	if (Life_Dist <= 0) {
		Destroy();
	}

	Position.z += 3.0f;
	Life_Dist -= 3.0f ;

	/*std::vector<Enemy*> enemylist = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);

	for (Enemy* trg : enemylist) {

		D3DXVECTOR3 ep = trg->Position;
		D3DXVECTOR3 dir = Position - ep;

		float length = D3DXVec3Length(&dir);

		if (length < 5.5f) {
			Effect* obj = Application::GetScene()->AddGameObject<Effect>(ObjectLayer);
			obj->Position = Position;
			obj->SetHW(8, 6);
			trg->Destroy();
			Destroy();
			return;
		}
	}*/

}

void Bullet::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;


	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}