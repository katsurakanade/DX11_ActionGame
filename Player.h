#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;

class Player : public Resource
{

private:

	float mHpInit = 40000.0f;
	bool mCanJump;
	float mJumpVel = 0;
	float mJumpTime = 0;
	float mAnimationSpeed = 3.0f;

	std::string mAnimationState = "Idle";

	AssimpModel* mModel;

	float mFrame = 0;

	void SettingPanel();

	void Jump(BYTE keykode);
	void Movement(BYTE keykodeF, BYTE keykodeB,BYTE keykodeR, BYTE keykodeL);
	void Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3);

	Animation* mpAnination;

public:

	int mNowController;
	float mHp;

	void Init();
	void Unint();
	void Update();
	void Render();

	float GetHpInit(){ return mHpInit; };
};

