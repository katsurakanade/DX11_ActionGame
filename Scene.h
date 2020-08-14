#pragma once
#include <list>
#include <typeinfo>
#include "main.h"
#include "Resource.h"
#include "Camera.h"
#include "Arrow.h"
#include "Sprite.h"
#include "Effect.h"
#include "Light.h"
#include "Skybox.h"
#include "Physical.h"
#include "field.h"
#include "Level.h"
#include "Player.h"
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

		Sprite* sp = AddGameObject<Sprite>(SpriteLayer);
		sp->SetTexture(Asset::GetTexture(TEXTURE_ENUM::SAMURAI));
		sp->SetPosition(D3DXVECTOR2(100, 900));

		Sprite* sp2 = AddGameObject<Sprite>(SpriteLayer);
		sp2->SetTexture(Asset::GetTexture(TEXTURE_ENUM::WIZARD));
		sp2->SetPosition(D3DXVECTOR2(300, 900));

		AddGameObject<Skybox>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);

		Level* level = AddGameObject<Level>(ObjectLayer);
		Player* player = AddGameObject<Player>(ObjectLayer);

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