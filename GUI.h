#pragma once

#include "Resource.h"
#include "Gauge.h"

class GUI : public Resource
{
private:

	Player* mpPlayer;
	Gauge* mpPlayerHP;


public:

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

