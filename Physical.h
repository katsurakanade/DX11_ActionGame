#pragma once

#include "Component.h"

class Physical : public Component
{

private:

	const float mSpeedDownCoefficient = 0.00005f;
	bool IsMoving();

public:

	float mSpeed_Start  = 0.02f;
	float mSpeed;
	D3DXVECTOR3 mVelocity;

	void Init();
	void Uninit();
	void Update(Resource* target);

	void Start();

	void AddForce(Resource* target,float force);

	void SpeedDown(float value) {
		mSpeed -= value;
	}
};

