#include "main.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Scene.h"
#include "input.h"
#include "Shader.h"
#include "ImageManager.h"

void Sprite::Init() {

	mImage = AddComponent<ImageManager>();
	mImage->SetResource(this);

	mImage->Position = Position;
	mImage->Scale = Scale;
	
}

void Sprite::Uninit() {

	Resource::Uninit();
}

void Sprite::Update() {

	mImage->Position = Position;
	mImage->Scale = Scale;

	if (!mImage->GetIsBillBoard()) {
		ImGui::Begin("GUI Editor");
		if (ImGui::TreeNode(Name.c_str())) {
			ImGui::SliderFloat3("Postition", Position, 0, 1920);
			ImGui::TreePop();
		}
		ImGui::End();

		mImage->Set2DPosition(Position);
	}

	Resource::Update();
}

void Sprite::Render() {

	mImage->Render();

}
