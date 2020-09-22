#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Animation;

class Enemy : public Resource
{
private:

	static int ID;

	AssimpModel* mModel;
	float mHpInit;
	float mHp;

	Gauge* mGauge;

	Animation* mpAnination;

	float change;
	int change_fr;
	int arrow;
	bool start = false;


public:
	void Init();
	void Uninit();
	void Update();
	void Render();

	void AddGauge();
	void Attack();
	void Movement(int arrow);

	void LookAt();
};

