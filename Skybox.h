#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class Skybox :public Resource
{

private:

	AssimpModel* m_Model;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

