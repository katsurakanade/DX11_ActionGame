#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "ModelManager.h"
#include "Animation.h"

void ModelManager::Init() {

	Name = "ModelManager";
	mpAnimation = GetResource()->GetComponent<Animation>();
	mIndependence = false;
}

void ModelManager::Uninit() {

	if (mIndependence) {
		mModel->Unload();
		delete mModel;
		mModel = nullptr;
	}
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

void ModelManager::LoadModelWithAnimation(std::string path) {

	mModel = new AssimpModel(true);
	mModel->Load(path);
	mModel->LoadAnimation("asset\\animation\\Idle.fbx", "Idle");
	mModel->LoadAnimation("asset\\animation\\Running.fbx", "Running");
	mModel->LoadAnimation("asset\\animation\\Attack.fbx", "Attack");
	mModel->LoadAnimation("asset\\animation\\Dying.fbx", "Dying");
	mIndependence = true;
}