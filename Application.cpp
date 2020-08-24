#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "input.h"
#include "Game.h"
#include "Title.h"
#include "Time.h"

Scene* Application::mScene;
bool Application::mDisableLighting;

bool Application::Init() {

	mDisableLighting = false;

	Input::Init();
	Renderer::Init();
	Asset::LoadSceneAsset();

	mScene = new Title();
	mScene->Init();

	return true;
}

void Application::Uninit() {

	mScene->Uninit();
	delete mScene;

	Asset::UnloadSceneAsset();

	Renderer::Uninit();
	Input::Uninit();

}

void Application::Update() {
		
	Input::Update();
	mScene->Update();

	{
		ImGui::Begin(u8"システム");
		ImGui::Text("Frame Time %f", Time::GetDeltaTime());
		ImGui::Checkbox(u8"線描画モード", &Renderer::mLineMode);
		ImGui::Checkbox(u8"Gizmosモード", &Renderer::mGizmosMode);
		ImGui::Checkbox(u8"ライト閉め", &mDisableLighting);
		ImGui::End();
	}

	Application::GetScene()->GetGameObject<Light>(CameraLayer)->GetSource()->Enable = !mDisableLighting;

}

void Application::Render() {

	Renderer::Begin();
	mScene->Render();
	Renderer::End();
}