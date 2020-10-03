/*
タイムクラス
*/

#pragma once

#include "main.h"

class Time
{
private:

	static std::chrono::system_clock::time_point mPreviousTime;
	static std::chrono::duration<double> mDelta;
	
public:

	// DeltaTime取得
	static float GetDeltaTime() { return (float)mDelta.count(); };

	static void Tick() {
		mDelta = std::chrono::system_clock::now() - mPreviousTime;
		mPreviousTime = std::chrono::system_clock::now();
	}


};