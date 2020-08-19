#pragma once

#include "Resource.h"

class GUI : public Resource
{
private:

	Player* mpPlayer;

public:

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

