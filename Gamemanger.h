#pragma once

#include "Resource.h"

enum RoundState {
	PLAYER_ROUND,
	ENEMY_ROUND,
};

class Gamemanger : public Resource
{

private:


public:
	RoundState mState;
	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

