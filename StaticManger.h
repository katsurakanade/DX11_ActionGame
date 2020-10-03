/*
�X�^�e�B�b�N�}�l�[�W���[
(�Q�[���̃O���[�o�����p)
*/
#pragma once

#include "main.h"

class StaticManger
{

public:

	// �ėp
	static std::map<std::string, std::string> StateMap;

	static void Init() {
		StateMap.insert(std::pair<std::string, std::string>("GameClear", "false"));
	};

	static void Uninit() {
		StateMap.erase(StateMap.begin(), StateMap.end());
	}
};

