#pragma once

#include "main.h"
#include "psapi.h"

class Debug
{

public:

	// ���s���ԕ\��(�R���\�[��)
	template <typename T>
	static void OutputRuntime(std::string title, T end, T start) {

		const std::chrono::duration<double> elapsed = end - start;

		std::string str = title + " Cost : " + std::to_string(elapsed.count()) + " sec";

		DebugOutputString(str.c_str());
	}

	// �g�p�������\��(�R���\�[��)(MB)
	static void OutputMemoryUsage() {
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		std::string str = "Memory Usage " + std::to_string(physMemUsedByMe >> 20) + " MB";
		DebugOutputString(str.c_str());
	}

};

