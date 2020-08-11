#pragma once

#include <chrono>

class Time
{
private:

	bool mRunning;

	std::chrono::time_point<std::chrono::steady_clock> mStart;
	std::chrono::time_point<std::chrono::steady_clock> mStop;

public:

	void Init();
	void Restart();
	bool Stop();
	bool Start();
	double GetMilisecondsElapsed();


};

