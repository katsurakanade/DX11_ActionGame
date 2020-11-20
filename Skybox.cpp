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
	Rotation = D3DXVECTOR3(-0.5f, 0.1f, 0.5f);
	Scale = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

}

void Skybox::Uninit() {

}

void Skybox::Update() {

	Position = Application::GetScene()->GetGameObject<Camera>(CameraLayer)->Position;
	Rotation.y += 0.001f * Time::GetDeltaTime();
}

void Skybox::Render() {


	D3DXMATRIX world = MakeWorldMatrix();

	Renderer::SetWorldMatrix(&world);

	mpModel->GetModel()->DefaultTexture = false;
	mpModel->GetModel()->SelectTextureIndex = TexutreIndex;

	Shader::Use(SHADER_TYPE_VSPS::Unlit);

	Renderer::SetRasterizerState(1);
	mpModel->Render(world);
	Renderer::SetRasterizerState(0);

}

