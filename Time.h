#pragma once

#include <chrono>

class Time
{
private:

	bool is_running;

	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;

public:

	void Init();
	void Restart();
	bool Stop();
	bool Start();
	double GetMilisecondsElapsed();


};

