#pragma once
#include "Resource.h"

class Player : public Resource
{
private:

	float mHp = 100.0f;

public:

	int mNowController;

	void Init();
	void Unint() {};
	void Update() {};
	void Render() {};

	void SelectBall();
};

