#pragma once

#include "Component.h"

class Physical : public Component
{

private:

	const float mSpeedDownCoefficient = 0.0001f;
	bool IsMoving();

public:

	float mSpeed_Start  = 0.2f;
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

