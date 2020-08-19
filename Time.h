#pragma once

#include "main.h"

class Time
{
private:

	static DWORD mPreviousTime;
	static DWORD mDelta;

public:

	static DWORD GetDeltaTime() { return mDelta; };

	static void Tick() {
		mDelta = timeGetTime() - mPreviousTime;
		mPreviousTime = timeGetTime();
	}


};