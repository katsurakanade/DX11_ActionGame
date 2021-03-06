/*
アプリケーションクラス
*/

#pragma once

#include "Scene.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"

class Application
{

private:

	// シーン
	static Scene* mScene;
	// フラグ
	static bool mDisableLighting;
	static bool mGizmosMode;
	// ForDebug
	static float mFrameTime[100];
	static float mMemoryUsage[100];
	static int mAnalysisCount;
	static float mUpdateAnalysisTime;
	static float mFPS;

	static ShaderParameter mShaderParameter;

public:

	static bool Init();
	static void Uninit();
	static void Update();
	static void Render();

	static std::random_device RandomDevice;
	static std::default_random_engine RandomGen;

	// Getter
	static Scene* GetScene() { return mScene; };

	// ForDebug
	static void System();

	// シーン遷移
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

	// フラグSetter
	static void UseLighting(bool val) {
		mDisableLighting = val;
	}

	static bool GetGizmosMode() { return mGizmosMode; };
	
};

