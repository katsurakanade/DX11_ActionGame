#pragma once

#include "Time.h"

class Application
{

private:

	static class Scene* _scene;
	static float DeltaTime;
	static float FpsTime;
	static int FpsCount;
	
	static Time Timer;
	static Time FpsTimer;

	static bool DisableLighting;

public:

	static bool Init();
	static void Uninit();
	static void Update();
	static void Render();
	static class Scene* GetScene() { return _scene; };
	static float GetDeltaTime() { return DeltaTime; };
};

