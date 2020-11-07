/*
プロップクラス
*/
#pragma once

#include "Resource.h"

class ModelManager;
class BoxCollider;

class Props : public Resource
{

private:

	// モデルポインタ
	ModelManager* mpModel;
	// Colliderポインタ
	BoxCollider* mpCollider;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

