#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Props.h"
#include "input.h"
#include "Particle.h"
#include "Shader.h"

void Props::Init() {

	Name = "Props";

	Position = D3DXVECTOR3(0, 0, 0);
	Rotation = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

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

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	Shader::Use(SHADER_TYPE_VSPS::Default);

	if (mModel) {
		mModel->Draw(world);
	}

}