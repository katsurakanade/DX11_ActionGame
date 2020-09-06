#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Player : public Resource
{
private:

	float mHpInit = 40000.0f;
	bool mCanJump;
	float mJumpVel = 0;
	float mJumpTime = 0;

	AssimpModel* mModel;

	void SettingPanel();

	void Jump(BYTE keykode);
	void Movement(BYTE keykodeR, BYTE keykodeL);
	void Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3);

public:

	int mNowController;
	float mHp;

	void Init();
	void Unint();
	void Update();
	void Render();

	float GetHpInit(){ return mHpInit; };
};

