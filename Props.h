/*
プロップクラス
*/
#pragma once

#include "Resource.h"

class Props : public Resource
{
	// モデル
	AssimpModel* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetModel(AssimpModel* model) { mModel = model; };
};

