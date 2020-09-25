#pragma once
#include <list>
#include <typeinfo>
#include "main.h"
#include "Resource.h"
#include "Camera.h"
#include "Effect.h"
#include "Light.h"
#include "Fade.h"
#include "Gamemanger.h"
#include "Time.h"
#include "Asset.h"

enum RenderLayer {
	CameraLayer , ObjectLayer ,EffectLayer, SpriteLayer , SpriteLayer2, FadeLayer , EndLayer
};

class Scene {

protected:

	std::list<Resource*> mGameObject[EndLayer];

	bool mSwitchFlag = false;
	bool mClear = false;

	Fade* mpFade;
	Asset* mAsset;

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

			for (int i = 0; i < EndLayer; i++) {
				for (Resource* g : mGameObject[i])
				{
					std::string str = g->Name.c_str();
					ImGui::Text(str.c_str());
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

	void SetSwitchFlag(bool val) { mSwitchFlag = val; };

	Asset* GetAsset() { return mAsset; };
};