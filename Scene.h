/*
シーンクラス
*/

#pragma once
#include <list>
#include <typeinfo>
#include "main.h"
#include "Resource.h"
#include "Camera.h"
#include "Light.h"
#include "Fade.h"
#include "Time.h"
#include "Asset.h"

// レイヤー
enum RenderLayer {
	 CameraLayer , ObjectLayer ,EffectLayer, EffectLayer2 ,SpriteLayer , SpriteLayer2, ParticleLayer,FadeLayer , EndLayer
};

class Scene {

protected:

	// オブジェクト
	std::list<Resource*> mGameObject[EndLayer];
	std::vector<std::string> mRenderLayerString{"CameraLayer" , "ObjectLayer" ,"EffectLayer", "EffectLayer2" ,"SpriteLayer" , "SpriteLayer2", "ParticleLayer","FadeLayer"  , "EndLayer" };

	// ゲームクリア用
	bool mSwitchFlag = false;
	bool mClear = false;

	// フェイドポインタ
	Fade* mpFade;
	// シーンアセット
	Asset* mAsset;
	// メインカメラ
	Camera* mMaincamera;

public:
	
	virtual void Init() = 0;

	virtual void Uninit() {
		
		for (int i = 0; i < EndLayer; i++) {
			for (Resource* g : mGameObject[i]) {
				g->Uninit();
				delete g;
			}
		}

		for (int i = 0; i < EndLayer; i++) {
			mGameObject[i].clear();
		}

		mAsset->UnloadSceneAsset();
		delete mAsset;
		mAsset = nullptr;
	}

	virtual void Update() {

		for (int i = 0; i < EndLayer; i++) {
			for (Resource* g : mGameObject[i])
			{
				g->Update();
			}
		}

		for (int i = 0; i < EndLayer; i++) {
			for (Resource* g : mGameObject[i])
			{
				g->FixedUpdate();
			}
		}

		for (int i = 0; i < EndLayer; i++) {
			mGameObject[i].remove_if([](Resource* obj) {return obj->Remove(); });
		}

		// Imgui オブジェクトリスト
		{
			ImGui::Begin(u8"オブジェクト");

			for (int i = CameraLayer; i < EndLayer; i++) {
				if (ImGui::TreeNode(mRenderLayerString[i].c_str())) {
					for (Resource* g : mGameObject[i])
					{
						ImGui::Text(g->Name.c_str());
					}
					ImGui::TreePop();
				}

			}
		
			ImGui::End();
		}

	}

	virtual void Render() {

		for (int i = 0; i < EndLayer; i++) {
			for (Resource* g : mGameObject[i])
			{
				if (g->GetActive()) {
					g->Render();
				}
			}
		}
	}

	virtual void AfterRender() {

		
	}

	template <typename T>
	T* AddGameObject(int layer) {
		T* gameObject = new T();
		mGameObject[layer].emplace_back(gameObject);
		gameObject->Init();
		return gameObject;
	};

	template <typename T>
	T* AddGameObject_Front(int layer) {
		T* gameObject = new T();
		mGameObject[layer].push_front(gameObject);
		gameObject->Init();
		return gameObject;
	};

	template <typename T>
	T* GetGameObject(int layer) {
		for (Resource* obj :  mGameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				return (T*)obj;
			}
		}
		return NULL;
	};

	template <typename T>
	std::vector<T*> GetGameObjects(int layer) {
		std::vector<T*> objects;
		for (Resource* obj : mGameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				objects.emplace_back((T*)obj);
			}
		}
		return objects;
	};

	// Setter
	void SetSwitchFlag(bool val) { mSwitchFlag = val; };
	// Getter
	Asset* GetAsset() { return mAsset; };
	Camera* GetMainCamera() { return mMaincamera; };
};