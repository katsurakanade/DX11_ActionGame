#pragma once

#include "Component.h"

class Animation : public Component
{
private:
	
	std::string mState;
	std::string mNewState;
	float mFrame = 0;
	float mCoefficient = 1.0f;
	float mAnimationSpeed = 3.0f;
	float mBlend;

	void DataPanel();
	bool DebugPanel = false;

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

	void SetCoefficient(float val) { mCoefficient = val; };
	void SetState(std::string str) { mState = str; };
	void SetNewState(std::string str) { mNewState = str; };
	void SetNewStateOneTime(std::string str) { mNewState = str;};

	std::string GetState() { return mState; };
	std::string GetNewState() { return mNewState; };

	int GetFrame() { return (int)mFrame; };
	float GetBlend() { return mBlend; };

};

