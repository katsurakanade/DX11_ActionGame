#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class BackGround : public Resource
{
private:

	AssimpModel* m_Model;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

};

