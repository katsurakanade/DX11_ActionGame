#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Enemy : public Resource
{
private :

	AssimpModel* mModel;
	
	float hp = 50.0f;

public:
	void Init();
	void Unint();
	void Update();
	void Render();
};

