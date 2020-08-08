#pragma once
#include <list>
#include <typeinfo>
#include "main.h"
#include "Resource.h"
#include "Camera.h"
#include "Player.h"
#include "Sprite.h"
#include "Light.h"
#include "Skybox.h"
#include "BackGround.h"
#include "Wall.h"
#include "Time.h"
#include "Asset.h"


enum RenderLayer {
	CameraLayer, ObjectLayer, SpriteLayer
};

class Scene {

protected:

	std::list<Resource*> GameObject[3];

	Assimp::Importer importer;

public:
	
	Scene() {};
	virtual ~Scene() {  };

	virtual void Init() {

		Asset::LoadSceneAsset();

		AddGameObject<Camera>(CameraLayer);
		AddGameObject<Light>(CameraLayer);

		AddGameObject<Skybox>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);
		AddGameObject<Player>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);
		AddGameObject<Wall>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 10);

	}

	virtual void Uninit() {

		for (int i = 0; i < 3; i++) {
			for (Resource* g : GameObject[i]) {
				g->Uninit();
				delete g;
			}
		}

		for (int i = 0; i < 3; i++) {
			GameObject[i].clear();
		}
		

		Asset::UnloadSceneAsset();
	}

	virtual void Update() {

		for (int i = 0; i < 3; i++) {
			for (Resource* g : GameObject[i])
			{
				g->Update();
			}
		}

	
		for (int i = 0; i < 3; i++) {
			GameObject[i].remove_if([](Resource* obj) {return obj->Remove(); });
		}

		/*{
			ImGui::Begin(u8"オブジェクト");
			ImGui::SetWindowPos(ImVec2(SCREEN_WIDTH - 200, 0));
			ImGui::SetWindowSize(ImVec2(200, SCREEN_HEIGHT));

			for (int i = 0; i < 3; i++) {
				for (Resource* g : GameObject[i])
				{
					ImGui::Text(g->Name.c_str());
				}
			}
		
			ImGui::End();
		}*/

	}

	virtual void Render() {



		for (int i = 0; i < 3; i++) {

			for (Resource* g : GameObject[i])
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
		GameObject[layer].push_back(gameObject);
		gameObject->Init();
		return gameObject;
	};

	template <typename T>
	T* GetGameObject(int layer) {
		for (Resource* obj :  GameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				return (T*)obj;
			}
		}
		return NULL;
	};

	template <typename T>
	std::vector<T*> GetGameObjects(int layer) {
		std::vector<T*> objects;
		for (Resource* obj : GameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				objects.push_back((T*)obj);
			}
		}
		return objects;
	};

	
};