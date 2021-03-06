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

// Static
Scene* Application::mScene = nullptr;
bool Application::mDisableLighting;
bool Application::mGizmosMode;
float Application::mFrameTime[100];
float Application::mMemoryUsage[100];
int Application::mAnalysisCount;
float Application::mUpdateAnalysisTime;
float Application::mFPS;
std::random_device Application::RandomDevice;
std::default_random_engine Application::RandomGen = std::default_random_engine(RandomDevice());
ShaderParameter Application::mShaderParameter;

std::map<std::string, std::string> StaticManger::StateMap;

bool Application::Init() {
 
	Input::Init();
	Renderer::Init();
	AudioListener::Init();
	AudioListener::SetVolume(0.5f);
	StaticManger::Init();

	mDisableLighting = false;
	mGizmosMode = false;

	mScene = new Title();
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
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	System();
	Input::Update();
	mScene->Update();


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

	Renderer::SetParameter(mShaderParameter);

	mScene->Render();
	mScene->AfterRender();
	Renderer::End();
}

void Application::System() {

	std::string str = "Memory Usage : " + std::to_string(Debug::GetMemoryUsage()) + " KB";

	mFrameTime[mAnalysisCount] = Time::GetDeltaTime();
	mMemoryUsage[mAnalysisCount] = Debug::GetMemoryUsage();

	// ImGui
	{
		ImGui::Begin(u8"システム");
		ImGui::Text("FPS : %f", mFPS);
		ImGui::Text("Frame Time : %f", Time::GetDeltaTime());
		ImGui::PlotLines("", mFrameTime, IM_ARRAYSIZE(mFrameTime));
		ImGui::Text(str.c_str());
		ImGui::PlotLines("", mMemoryUsage, IM_ARRAYSIZE(mMemoryUsage));
		ImGui::Checkbox(u8"線描画モード", &Renderer::mLineMode);
		ImGui::Checkbox(u8"Gizmosモード", &mGizmosMode);
		ImGui::End();
	}

	if (mUpdateAnalysisTime > 100) {
		mAnalysisCount++;
		mUpdateAnalysisTime = 0.0f;
		mFPS = 1.0f / Time::GetDeltaTime();
	}

	if (mAnalysisCount >= 100) {
		mAnalysisCount = 0;
	}

	mUpdateAnalysisTime++;

}