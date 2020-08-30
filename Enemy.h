#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Enemy : public Resource
{
private:

	static int ID;

	AssimpModel* mModel;
	float mHpInit;
	float mHp;

	Gauge* mGauge;

public:
	void Init();
	void Uninit();
	void Update();
	void Render();

	void AddGauge();
	void Attack();
};

