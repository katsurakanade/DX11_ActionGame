#pragma once
#include <list>
#include <typeinfo>
#include "main.h"
#include "Resource.h"
#include "Camera.h"
#include "Player.h"
#include "Sprite.h"
#include "Effect.h"
#include "Light.h"
#include "Skybox.h"
#include "Physical.h"
#include "field.h"
#include "Wall.h"
#include "Time.h"
#include "Asset.h"

enum RenderLayer {
	CameraLayer ,ObjectLayer , EffectLayer, SpriteLayer
};

class Scene {

protected:

	std::list<Resource*> mGameObject[4];

public:
	
	Scene() {};
	virtual ~Scene() {  };

	virtual void Init() {

		Asset::LoadSceneAsset();

		AddGameObject<Camera>(CameraLayer);
		AddGameObject<Light>(CameraLayer);

		/*Sprite* sp = AddGameObject<Sprite>(SpriteLayer);
		sp->SetTexture(Asset::GetTexture(TEXTURE_ENUM::NUMBER));
		sp->SetAnimationSprite(true);
		sp->SetFrame(5);
		sp->SetHW(5, 5);*/

		AddGameObject<Skybox>(ObjectLayer)->Position = D3DXVECTOR3(0, 0, 0);

		Player* p1 = AddGameObject<Player>(ObjectLayer);
		p1->Position = D3DXVECTOR3(0, 20, 10);
		p1->SetTexture(TEXTURE_ENUM::DIRT);

		Wall* top = AddGameObject<Wall>(ObjectLayer);
		top->Position = D3DXVECTOR3(0, 50, 20);
		top->Rotation = D3DXVECTOR3(0, 0, 0);
		top->Scale = D3DXVECTOR3(50, 1, 50);
		top->SetFront(D3DXVECTOR3(0, -1, 0));
		top->ResetPositionOffest();

		Wall* ground = AddGameObject<Wall>(ObjectLayer);
		ground->Position = D3DXVECTOR3(0, 0, 20);
		ground->Rotation = D3DXVECTOR3(0, 0, 0);
		ground->Scale = D3DXVECTOR3(50, 1, 50);
		ground->SetFront(D3DXVECTOR3(0, 1, 0));
		ground->ResetPositionOffest();

		Wall* right = AddGameObject<Wall>(ObjectLayer);
		right->Position = D3DXVECTOR3(25, 0, 20);
		right->Rotation = D3DXVECTOR3(0, 0, 0);
		right->Scale = D3DXVECTOR3(1,50,50);
		right->SetFront(D3DXVECTOR3(-1,0,0));
		right->ResetPositionOffest();

		Wall* left = AddGameObject<Wall>(ObjectLayer);
		left->Position = D3DXVECTOR3(-25, 0, 20);
		left->Rotation = D3DXVECTOR3(0, 0, 0);
		left->Scale = D3DXVECTOR3(1, 50, 50); 
		left->SetFront(D3DXVECTOR3(1, 0, 0));
		left->ResetPositionOffest();

		/*Wall* Front = AddGameObject<Wall>(ObjectLayer);
		Front->Position = D3DXVECTOR3(0, 0, -5);
		Front->Rotation = D3DXVECTOR3(0, 0, 0);
		Front->Scale = D3DXVECTOR3(50, 50, 1);
		Front->SetFront(D3DXVECTOR3(0, 0, 1));
		Front->ResetPositionOffest();*/
	
		Wall* Back = AddGameObject<Wall>(ObjectLayer);
		Back->Position = D3DXVECTOR3(0, 0, 45);
		Back->Rotation = D3DXVECTOR3(0, 0, 0);
		Back->Scale = D3DXVECTOR3(50, 50, 1);
		Back->SetFront(D3DXVECTOR3(0, 0, -1));
		Back->ResetPositionOffest();

	}

	virtual void Uninit() {

		for (int i = 0; i < 4; i++) {
			for (Resource* g : mGameObject[i]) {
				g->Uninit();
				delete g;
			}
		}

		for (int i = 0; i < 4; i++) {
			mGameObject[i].clear();
		}

		Asset::UnloadSceneAsset();
	}

	virtual void Update() {

		for (int i = 0; i < 4; i++) {
			for (Resource* g : mGameObject[i])
			{
				g->Update();
			}
		}

	
		for (int i = 0; i < 4; i++) {
			mGameObject[i].remove_if([](Resource* obj) {return obj->Remove(); });
		}

		{
			ImGui::Begin(u8"オブジェクト");

			for (int i = 0; i < 4; i++) {
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