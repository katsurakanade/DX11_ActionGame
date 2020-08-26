#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class Skybox :public Resource
{

private:

	AssimpModel* mModel;

	int TexutreIndex = 4;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetModelTexture(int val) {
		TexutreIndex = val;
	}
};

