#include "main.h"
#include "Renderer.h"
#include "Skybox.h"
#include "Application.h"
#include "Scene.h"
#include "Shader.h"
#include "ModelManager.h"

void Skybox::Init() {

	Name = "Skybox";

	mpModel = AddComponent<ModelManager>();

	if (Application::GetAsset()->GetScene() == SCENE_ASSET::TITLE) {
		mpModel->SetModel(Application::GetScene()->GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_TITLE::BALL));
	}

	if (Application::GetAsset()->GetScene() == SCENE_ASSET::GAME) {
		mpModel->SetModel(Application::GetScene()->GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::BALL));
	}

	Position = D3DXVECTOR3(0, 0, 0); 
	Rotation = D3DXVECTOR3(2.1f, 0.4f, 0.0f);
	Scale = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

}

void Skybox::Uninit() {

}

void Skybox::Update() {

	Position = Application::GetScene()->GetGameObject<Camera>(CameraLayer)->Position;

}

void Skybox::Render() {



	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;
	ID3D11RasterizerState* rs;
	Renderer::GetDevice()->CreateRasterizerState(&rd, &rs);
	Renderer::GetDeviceContext()->RSSetState(rs);

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	mpModel->GetModel()->DefaultTexture = false;
	mpModel->GetModel()->SelectTextureIndex = TexutreIndex;

	Shader::Use(SHADER_TYPE_VSPS::Unlit);

	mpModel->Render(world);

}

