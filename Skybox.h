/*
スカイボックスクラス
*/
#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class Skybox :public Resource
{

private:
	
	// モデル
	AssimpModel* mModel;
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

