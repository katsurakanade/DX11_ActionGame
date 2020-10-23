/*
スカイボックスクラス
*/
#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class ModelManager;

class Skybox :public Resource
{

private:

	// モデルポインタ
	ModelManager* mpModel;
	// テクスチャインデックス
	int TexutreIndex = 4;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetModelTexture(int val) {
		TexutreIndex = val;
	}
};

