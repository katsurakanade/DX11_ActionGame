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

	Resource::Update();
}

void Sprite::Render() {

	mImage->Render();

}
