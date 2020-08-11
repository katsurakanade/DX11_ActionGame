#pragma once

#include "Time.h"

class Application
{

private:

	static class Scene* mScene;
	static float mDeltaTime;
	static float mFpsTime;
	static int mFpsCount;
	
	static Time mTimer;
	static Time mFpsTimer;

	static bool mDisableLighting;


public:

	static bool Init();
	static void Uninit();
	static void Update();
	static void Render();
	static class Scene* GetScene() { return mScene; };
	static float GetDeltaTime() { return mDeltaTime; };
};

