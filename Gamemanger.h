#pragma once

#include "Resource.h"

enum class RoundState{
	PLAYER_ROUND,
	ENEMY_ROUND,
};

class Gamemanger : public Resource
{

private:

	bool mGameClear = false;

	void GameClear();

public:

	RoundState mState;
	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

