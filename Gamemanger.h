#pragma once

#include "Resource.h"
#include "Level.h"

enum class RoundState{
	PLAYER_ROUND,
	ENEMY_ROUND,
};


class Gamemanger : public Resource
{

private:

	bool mGameClear = false;

	int mRound;

	Level* mpLevel;

	void GameClear(bool win);

public:

	RoundState mState;

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

