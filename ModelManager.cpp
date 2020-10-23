#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "ModelManager.h"
#include "Animation.h"

void ModelManager::Init() {

	Name = "ModelManager";

}

void ModelManager::Uninit() {

}

void ModelManager::Update() {

	if (mpAnimation) {
		mModel->Update(mpAnimation->GetState().c_str(), mpAnimation->GetNewState().c_str(), mpAnimation->GetBlend(), mpAnimation->GetFrame());
	}
	
}

void ModelManager::FixedUpdate() {

}


void ModelManager::Render(D3DXMATRIX world) {
	mModel->Draw(world);
}