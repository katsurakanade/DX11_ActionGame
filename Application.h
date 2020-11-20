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
	// シーンアセット
	static Asset* mAsset;

	// フラグ
	static bool mDisableLighting;
	static bool mUsingGPU;
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

	// Setter
	static void SetAsset(Asset* asset) { mAsset = asset; };

	// Getter
	static Scene* GetScene() { return mScene; };
	static Asset* GetAsset() { return mAsset; };
	static bool GetUsingGPU() { return mUsingGPU; };

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
	static void UseGPUCompute(bool val) {
		mUsingGPU = val;
	}

	
};

