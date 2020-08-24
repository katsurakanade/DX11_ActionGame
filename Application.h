#pragma once

#include "Scene.h"
#include "Title.h"
#include "Game.h"

class Application
{

private:

	static Scene* mScene;

	static bool mDisableLighting;

public:

	static bool Init();
	static void Uninit();
	static void Update();
	static void Render();
	static Scene* GetScene() { return mScene; };

	template <typename T>
	static void SwitchScene() {

		if (mScene) {
			mScene->Uninit();
			delete mScene;
		}
		
		T* scene = new T();
		mScene = scene;
		scene->Init();
	}

};

