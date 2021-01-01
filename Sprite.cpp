#include "main.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Scene.h"
#include "input.h"
#include "Shader.h"
#include "ImageManager.h"
#include "Collision.h"

void Sprite::Init() {

	mImage = AddComponent<ImageManager>();

	mImage->Position = Position;
	mImage->Rotation = Rotation;
	mImage->Scale = Scale;
	
}

void Sprite::Uninit() {

	Resource::Uninit();
}

void Sprite::Update() {

	mImage->Position = Position;
	mImage->Rotation = Rotation;
	mImage->Scale = Scale;

	if (!mImage->GetIsBillBoard()) {
	

		mImage->Set2DPosition(Position);
	}

	Resource::Update();
}

void Sprite::Render() {

	mImage->Render();

}
