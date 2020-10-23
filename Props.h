/*
プロップクラス
*/
#pragma once

#include "Resource.h"

class ModelManager;

class Props : public Resource
{

private:

	// モデルポインタ
	ModelManager* mpModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

