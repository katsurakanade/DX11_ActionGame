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
	mpModel->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));

	Position = D3DXVECTOR3(0, 0, 0);
	Rotation = D3DXVECTOR3(0, 1.57f, 0);
	Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

	mpCollider = AddComponent<BoxCollider>();
	mpCollider->mPositionOffest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mpCollider->mScaleOffestCoff = D3DXVECTOR3(1.11f, -0.37f, -0.73f);

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

	D3DXMATRIX world = MakeWorldMatrix();
	Renderer::SetWorldMatrix(&world);
	Shader::Use(SHADER_TYPE_VSPS::Default);
	mpModel->Render(world);
	GetComponent<BoxCollider>()->Render();

}