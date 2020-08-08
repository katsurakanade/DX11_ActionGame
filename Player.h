#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Collision.h"

class Player : public Resource
{
private:
	
	float Speed = 0.1f;
	AssimpModel* m_Model;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

};

