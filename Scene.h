#pragma once
#include <list>
#include <typeinfo>
#include "main.h"
#include "Resource.h"
#include "Camera.h"
#include "Effect.h"
#include "Light.h"
#include "Skybox.h"
#include "Physical.h"
#include "Level.h"
#include "Player.h"
#include "GUI.h"
#include "Gamemanger.h"
#include "Time.h"
#include "Asset.h"

enum RenderLayer {
	CameraLayer , ObjectLayer , EffectLayer, SpriteLayer
};

class Scene {

protected:

	std::list<Resource*> mGameObject[5];

public:
	
	Scene() {};
	virtual ~Scene() {  };

	virtual void Init() {

		Asset::LoadSceneAsset();

		AddGameObject<Camera>(CameraLayer);
		AddGameObject<Light>(CameraLayer);

		AddGameObject<Skybox>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);

		Level* level = AddGameObject<Level>(ObjectLayer);
		Player* player = AddGameObject<Player>(ObjectLayer);
		Gamemanger* manger = AddGameObject<Gamemanger>(ObjectLayer);
		GUI* gui = AddGameObject<GUI>(SpriteLayer);

		
	}

	virtual void Uninit() {

		for (int i = 0; i < 5; i++) {
			for (Resource* g : mGameObject[i]) {
				g->Uninit();
				delete g;
			}
		}

		for (int i = 0; i < 5; i++) {
			mGameObject[i].clear();
		}

		Asset::UnloadSceneAsset();
	}

	virtual void Update() {

		for (int i = 0; i < 5; i++) {
			for (Resource* g : mGameObject[i])
			{
				g->Update();
			}
		}

	
		for (int i = 0; i < 5; i++) {
			mGameObject[i].remove_if([](Resource* obj) {return obj->Remove(); });
		}

		{
			ImGui::Begin(u8"オブジェクト");

			for (int i = 0; i < 5; i++) {
				for (Resource* g : mGameObject[i])
				{
					ImGui::Text(g->Name.c_str());
				}
			}
		
			ImGui::End();
		}

	}

	virtual void Render() {
		for (int i = 0; i < 4; i++) {
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
		mGameObject[layer].push_back(gameObject);
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
				objects.push_back((T*)obj);
			}
		}
		return objects;
	};

	
};