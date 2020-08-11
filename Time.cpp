#include "Time.h"



void Time::Init() {
	mStart = std::chrono::high_resolution_clock::now();
	mStop = std::chrono::high_resolution_clock::now();
	mRunning = false;
}

double Time::GetMilisecondsElapsed() {

	if (mRunning) {
		auto elapsed = std::chrono::duration<double, std::milli >(std::chrono::high_resolution_clock::now() - mStart);
		return elapsed.count();
	}

	else {
		auto elapsed = std::chrono::duration<double, std::milli >(mStop - mStart);
		return elapsed.count();
	}
}

void Time::Restart() {
	mRunning = true;
	mStart = std::chrono::high_resolution_clock::now();
}

bool Time::Stop() {

	if (!mRunning) {
		return false;
	}
	else {
		mStop = std::chrono::high_resolution_clock::now();
		mRunning = false;
		return true;
	}
}

bool Time::Start() {

	if (mRunning){
		return false;
	}

	else{
		mStart = std::chrono::high_resolution_clock::now();
		mRunning = true;
		return true;
	}
}