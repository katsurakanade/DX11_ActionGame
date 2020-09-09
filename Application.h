#pragma once

#include "Scene.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"

class Application
{

private:

	static Scene* mScene;
	static Asset* mAsset;

	static bool mDisableLighting;

public:

	static bool Init();
	static void Uninit();
	static void Update();
	static void Render();
	static Scene* GetScene() { return mScene; };
	static Asset* GetAsset() { return mAsset; };
	static void SetAsset(Asset* asset) { mAsset = asset; };

	static void System();

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

	static void UseLighting(bool val) {
		mDisableLighting = val;
	}
};

