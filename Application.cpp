#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "input.h"
#include "Scene.h"

Scene* Application::_scene;
float Application::DeltaTime;
float Application::FpsTime;
int Application::FpsCount;
Time Application::Timer;
Time Application::FpsTimer;

bool Application::DisableLighting;

bool Application::Init() {

	DisableLighting = false;

	Input::Init();
	Renderer::Init();

	Timer.Start();
	FpsTimer.Start();

	_scene = new Scene();
	_scene->Init();



	return true;
}

void Application::Uninit() {

	_scene->Uninit();
	delete _scene;

	Renderer::Uninit();
	Input::Uninit();

}

void Application::Update() {
	
	DeltaTime = (float)Timer.GetMilisecondsElapsed();
	Timer.Restart();
	
	Input::Update();
	_scene->Update();

	static int fpscount = 0;
	static std::string str = "FPS : 0 ";
	fpscount++;

	if (FpsTimer.GetMilisecondsElapsed() > 1000.0f) {
		str = "FPS:" + std::to_string(fpscount);
		fpscount = 0;
		FpsTimer.Restart();
	}

	{
		ImGui::Begin(u8"システム");
		ImGui::SetWindowSize(ImVec2(200, 200));
		ImGui::Text(str.c_str());
		ImGui::Checkbox(u8"線描画モード", &Renderer::LineMode);
		ImGui::Checkbox(u8"Gizmosモード", &Renderer::GizmosMode);
		ImGui::Checkbox(u8"ライト閉め", &DisableLighting);
		ImGui::End();
	}

	Application::GetScene()->GetGameObject<Light>(CameraLayer)->GetSource()->Enable = !DisableLighting;
}

void Application::Render() {

	Renderer::Begin();
	_scene->Render();
	
	Renderer::End();
}