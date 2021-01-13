#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Props.h"
#include "input.h"
#include "Particle.h"
#include "Shader.h"
#include "ModelManager.h"
#include "Collision.h"

void Props::Init() {

	Name = "Props";

	mpModel = AddComponent<ModelManager>();
	mpModel->SetModel(Asset::GetInstance()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));

	Position = D3DXVECTOR3(0, 0, 0);
	Rotation = D3DXVECTOR3(0, 1.57f, 0);
	Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

	D3DXQuaternionIdentity(&this->Quaternion);

	Resource::Init();
}

void Props::Uninit() {
	Resource::Uninit();
}

void Props::Update() {

	Resource::Update();
}

void Props::Render() {

	//if (!Application::GetScene()->GetMainCamera()->CheckInView(Position)) 
	//	return;

	D3DXMATRIX world = MakeWorldMatrix();
	Renderer::SetWorldMatrix(&world);
	Shader::Use(SHADER_TYPE_VSPS::WithNormal);
	mpModel->Render(world);

}