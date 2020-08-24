#include "main.h"
#include "input.h"
#include "Title.h"
#include "Application.h"

void Title::Init() {

	AddGameObject<Camera>(CameraLayer);
	AddGameObject<Light>(CameraLayer);

}

void Title::Update() {

	Scene::Update();

	if (Input::GetKeyPress(VK_SPACE)) {
		Application::SwitchScene<Game>();
	}

}
