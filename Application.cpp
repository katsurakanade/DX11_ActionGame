#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "input.h"
#include "AudioListener.h"
#include "Game.h"
#include "Title.h"
#include "Time.h"
#include "StaticManger.h"
#include "psapi.h"
#include "Debug.h"
#include <thread>

Scene* Application::mScene;
Asset* Application::mAsset;
bool Application::mDisableLighting;
std::map<std::string, std::string> StaticManger::StateMap;

bool Application::Init() {

	mDisableLighting = false;

	Input::Init();
	Renderer::Init();
	AudioListener::Init();
	AudioListener::SetVolume(1.0f);
	StaticManger::Init();

	mScene = new Game();
	mScene->Init();

	return true;
}

void Application::Uninit() {

	mScene->Uninit();
	delete mScene;
	mScene = nullptr;

	StaticManger::Uninit();

	Renderer::Uninit();
	Input::Uninit();
	AudioListener::Uninit();

}

void Application::Update() {
		
	Input::Update();
	mScene->Update();

	std::thread system(System);

	system.join();

	Application::GetScene()->GetGameObject<Light>(CameraLayer)->GetSource()->Enable = !mDisableLighting;

}

void Application::Render() {

	Renderer::Begin();
	mScene->Render();
	Renderer::End();
}

void Application::System() {

	std::string str = "Memory Usage : " + Debug::GetMemoryUsage();

	{
		ImGui::Begin(u8"�V�X�e��");
		ImGui::Text("Frame Time : %f", Time::GetDeltaTime());
		ImGui::Text(str.c_str());
		ImGui::Checkbox(u8"���`�惂�[�h", &Renderer::mLineMode);
		ImGui::Checkbox(u8"Gizmos���[�h", &Renderer::mGizmosMode);
		ImGui::Checkbox(u8"���C�g��", &mDisableLighting);
		ImGui::End();
	}
}