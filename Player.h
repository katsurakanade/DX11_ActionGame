#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Collision.h"

class Player : public Resource
{
private:
	
	float mSpeed = 0.2f;
	AssimpModel* mModel;

	void Reflect();

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetTexture(int index);
};

