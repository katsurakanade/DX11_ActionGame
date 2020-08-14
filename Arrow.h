#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Arrow : public Resource
{

	AssimpModel* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

