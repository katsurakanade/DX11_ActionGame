#pragma once

#include "Time.h"

class Application
{

private:

	static class Scene* mScene;

	static bool mDisableLighting;

public:

	static bool Init();
	static void Uninit();
	static void Update();
	static void Render();
	static class Scene* GetScene() { return mScene; };
};

