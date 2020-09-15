#pragma once

#include "Component.h"

class Animation : public Component
{
private:
	
	std::string mState;
	std::string mOldState;
	float mFrame = 0;
	float mCoefficient = 1.0f;
	float mAnimationSpeed = 3.0f;

	void DataPanel();

public:

	void Init();
	void Uninit();
	void Update();

	void SetCoefficient(float val) { mCoefficient = val; };
	void SetState(std::string str) { mState = str; };

	std::string GetState() { return mState; };
	int GetFrame() { return (int)mFrame; };

};

