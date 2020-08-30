#pragma once

#include "main.h"

class StaticManger
{

public:
	// Key,Value
	static std::map<std::string, std::string> StateMap;

	static void Init() {
		StateMap.insert(std::pair<std::string, std::string>("GameClear", "false"));
	};

	static void Uninit() {
		//StateMap.erase(StateMap.begin(), StateMap.end());
	}
};

