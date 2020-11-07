#pragma once
#include "Resource.h"
class LevelTools : public Resource
{

private:

	Resource* mpPlayer;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

