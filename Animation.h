/*
アニメーションクラス
*/

#pragma once

#include "Component.h"

class Animation : public Component
{

private:
	
	// 状態
	std::string mState;
	std::string mNewState;
	// フレーム
	float mFrame = 0;
	// 速度用係数
	float mCoefficient = 1.0f;
	float mAnimationSpeed = 3.0f;
	// ブレンド
	float mBlend;
	// ForDebug
	void DataPanel();
	bool DebugPanel = false;

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

	// Setter
	void SetCoefficient(float val) { mCoefficient = val; };
	void SetState(std::string str) { mState = str; };
	void SetNewState(std::string str) { mNewState = str; };
	void SetNewStateOneTime(std::string str) { mNewState = str;};

	// Getter
	std::string GetState() { return mState; };
	std::string GetNewState() { return mNewState; };
	int GetFrame() { return (int)mFrame; };
	float GetBlend() { return mBlend; };

};

