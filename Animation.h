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
	std::string mOldState;
	// フレーム
	float mFrame = 0;
	// 速度用係数
	float mCoefficient = 1.0f;
	// ブレンド
	float mBlend;
	// 一回アニメーション用
	bool mOneTimeFlag;
	float mWaitTime;
	float mTimeToWait;
	// 一時停止
	bool mPauseFrame;
	// ForDebug
	void DataPanel();

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

	// Setter
	void SetCoefficient(float val) { mCoefficient = val; };
	void SetState(std::string str) { mState = str; };
	void SetNewState(std::string str) { mNewState = str; };
	void SetNewStateOneTime(std::string str, float timetowait);
	void SetPause(bool val) { mPauseFrame = val; };

	// Getter
	std::string GetState() { return mState; };
	std::string GetNewState() { return mNewState; };
	int GetFrame() { return (int)mFrame; };
	float GetBlend() { return mBlend; };
	bool GetOneTimeFlag() { return mOneTimeFlag; };
	bool GetPause() { return mPauseFrame; };
};

