/*
GUI�N���X
*/
#pragma once

#include "Resource.h"
#include "Gauge.h"
#include "Digit.h"

class GUI : public Resource
{
private:

	// �I�u�W�F�N�g�|�C���^
	Player* mpPlayer;
	Gauge* mpPlayerHP;
	Digit* mpPlayerHPDigit;

public:

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

