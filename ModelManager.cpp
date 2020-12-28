#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "ModelManager.h"
#include "Animation.h"

void ModelManager::Init() {

	Name = "ModelManager";
	mpAnimation = GetResource()->GetComponent<Animation>();

}

void ModelManager::Uninit() {

}

void ModelManager::Update() {
	
	if (mModel->mResourceName == "Model") {
		mModel->mResourceName = GetResource()->Name;
	}

	if (mpAnimation) {
		mModel->Update(mpAnimation->GetState().c_str(), mpAnimation->GetNewState().c_str(), mpAnimation->GetBlend(), mpAnimation->GetFrame());
	}
	
}

void ModelManager::FixedUpdate() {
	Component::FixedUpdate();
}


void ModelManager::Render(D3DXMATRIX world) {
	mModel->Draw(world);
}