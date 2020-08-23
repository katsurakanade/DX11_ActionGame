#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Enemy : public Resource
{
private:

	static int ID;

	AssimpModel* mModel;
	float mHpInit = 50.0f;
	float mHp;

	Gauge* mGauge;

public:
	void Init();
	void Unint();
	void Update();
	void Render();

	void Attack();
};

