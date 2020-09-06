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

Scene* Application::mScene;
Asset* Application::mAsset;
bool Application::mDisableLighting;
std::map<std::string, std::string> StaticManger::StateMap;


bool Application::Init() {

	mDisableLighting = false;

	Input::Init();
	Renderer::Init();
	AudioListener::Init();
	AudioListener::SetVolume(0.1f);
	StaticManger::Init();

	Debug::OutputMemoryUsage();
	mAsset = new Asset();
	mAsset->LoadSceneAsset();
	Debug::OutputMemoryUsage();
	
	mScene = new Game();
	mScene->Init();


	return true;
}

void Application::Uninit() {

	mScene->Uninit();
	delete mScene;

	mAsset->UnloadSceneAsset();
	delete mAsset;
	mAsset = nullptr;
	Debug::OutputMemoryUsage();

	StaticManger::Uninit();

	Renderer::Uninit();
	Input::Uninit();
	AudioListener::Unint();

}

void Application::Update() {
		
	Input::Update();
	mScene->Update();

	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	std::string str = "Memory Usage : " + std::to_string(physMemUsedByMe >> 20) + " MB";

	{
		ImGui::Begin(u8"�V�X�e��");
		ImGui::Text("Frame Time : %f", Time::GetDeltaTime());
		ImGui::Text(str.c_str());
		ImGui::Checkbox(u8"���`�惂�[�h", &Renderer::mLineMode);
		ImGui::Checkbox(u8"Gizmos���[�h", &Renderer::mGizmosMode);
		ImGui::Checkbox(u8"���C�g��", &mDisableLighting);
		ImGui::End();
	}

	Application::GetScene()->GetGameObject<Light>(CameraLayer)->GetSource()->Enable = !mDisableLighting;

}

void Application::Render() {

	Renderer::Begin();
	mScene->Render();
	Renderer::End();
}