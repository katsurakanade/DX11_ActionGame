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
#include "FileManger.h"
#include <thread>

Scene* Application::mScene;
Asset* Application::mAsset;
bool Application::mDisableLighting;
bool Application::mUsingGPU;
float Application::mFrameTime[100];
float Application::mMemoryUsage[100];
int Application::mAnalysisCount;
float Application::mUpdateAnalysisTime;

std::map<std::string, std::string> StaticManger::StateMap;

bool Application::Init() {

	mDisableLighting = false;
	mUsingGPU = true;

	Input::Init();
	Renderer::Init();
	AudioListener::Init();
	AudioListener::SetVolume(1.0f);
	StaticManger::Init();

	Renderer::mGizmosMode = false;

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


}

void Application::Render() {

	Renderer::Begin();

	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(0.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetLight(light);

	mScene->Render();
	Renderer::End();
}

void Application::System() {

	std::string str = "Memory Usage : " + std::to_string(Debug::GetMemoryUsage()) + " KB";

	mFrameTime[mAnalysisCount] = Time::GetDeltaTime();
	mMemoryUsage[mAnalysisCount] = Debug::GetMemoryUsage();

	{
		ImGui::Begin(u8"システム");
		ImGui::Text("Frame Time : %f", Time::GetDeltaTime());
		ImGui::PlotLines("", mFrameTime, IM_ARRAYSIZE(mFrameTime));
		ImGui::Text(str.c_str());
		ImGui::PlotLines("", mMemoryUsage, IM_ARRAYSIZE(mMemoryUsage));
		ImGui::Checkbox(u8"線描画モード", &Renderer::mLineMode);
		ImGui::Checkbox(u8"Gizmosモード", &Renderer::mGizmosMode);
		ImGui::Checkbox(u8"ライト閉め", &mDisableLighting);
		ImGui::Checkbox(u8"GPUで計算する", &mUsingGPU);
		ImGui::End();
	}

	if (mUpdateAnalysisTime > 100) {
		mAnalysisCount++;
		mUpdateAnalysisTime = 0.0f;
	}

	if (mAnalysisCount >= 100) {
		mAnalysisCount = 0;
	}

	mUpdateAnalysisTime++;

}