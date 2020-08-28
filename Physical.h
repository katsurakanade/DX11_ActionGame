#pragma once

#include "Component.h"

class Physical : public Component
{

private:

	const float mSpeedDownCoefficient;
	bool IsMoving();

public:

	Physical() : mSpeedDownCoefficient(0.1f), mSpeed_Start(30.0f) {};

	float mSpeed_Start;
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

