#pragma once

#include "Component.h"

class Physical : public Component
{

public:

	D3DXVECTOR3 mVelocity;

	void Init();
	void Uninit();
	void Update(Resource* target);

	void AddForce(Resource* target,float force);

};

