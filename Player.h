#pragma once
#include "Resource.h"

class Player : public Resource
{
private:

	float mHpInit = 40000.0f;

public:

	int mNowController;
	float mHp;

	void Init();
	void Unint() {};
	void Update() {};
	void Render() {};

	void SelectBall();

	float GetHpInit(){ return mHpInit; };
};

