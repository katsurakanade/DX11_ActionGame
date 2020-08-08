#pragma once

#include "AssimpModel.h"
#include "Resource.h"
#include "Collision.h"

class Wall : public Resource
{
private:

	AssimpModel* m_Model;
	
public:

	void Init();
	void Uninit();
	void Update();
	void Render();

};

