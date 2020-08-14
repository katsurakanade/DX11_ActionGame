#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "input.h"
#include "Scene.h"

Scene* Application::mScene;
float Application::mDeltaTime;
float Application::mFpsTime;
int Application::mFpsCount;
Time Application::mTimer;
Time Application::mFpsTimer;

bool Application::mDisableLighting;

bool Application::Init() {

	mDisableLighting = false;

	Input::Init();
	Renderer::Init();

	mTimer.Start();
	mFpsTimer.Start();

	mScene = new Scene();
	mScene->Init();

	return true;
}

void Application::Uninit() {

	mScene->Uninit();
	delete mScene;

	Renderer::Uninit();
	Input::Uninit();

}

void Application::Update() {
	
	mTimer.Restart();
	
	Input::Update();
	mScene->Update();

	static int fpscount = 0;
	static std::string str = "FPS : 0 ";
	fpscount++;

	if (mFpsTimer.GetMilisecondsElapsed() > 1000.0f) {
		str = "FPS:" + std::to_string(fpscount);
		fpscount = 0;
		mFpsTimer.Restart();
	}

	{
		ImGui::Begin(u8"システム");
		ImGui::SetWindowSize(ImVec2(200, 200));
		ImGui::Text(str.c_str());
		ImGui::Text(u8"Frame Time : %f", mDeltaTime);
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