#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class Skybox :public Resource
{

private:

	AssimpModel* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

