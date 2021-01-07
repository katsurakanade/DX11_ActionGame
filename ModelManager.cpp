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
	mModel->LoadAnimation("asset\\animation\\Enemy\\Idle.fbx", "Idle");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Running.fbx", "Running");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Attack.fbx", "Attack");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Dying.fbx", "Dying");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Spell.fbx", "Spell");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Spell2.fbx", "Spell2");
	mModel->LoadAnimation("asset\\animation\\Enemy\\PowerUp.fbx", "PowerUp");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Jump_Attack.fbx", "Jump_Attack");
	mModel->LoadAnimation("asset\\animation\\Enemy\\Prepare.fbx", "Prepare");
	mIndependence = true;
}