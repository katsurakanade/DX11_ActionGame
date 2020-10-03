/*
GUIクラス
*/
#pragma once

#include "Resource.h"
#include "Gauge.h"
#include "Digit.h"

class GUI : public Resource
{
private:

	// オブジェクトポインタ
	Player* mpPlayer;
	Gauge* mpPlayerHP;
	Digit* mpPlayerHPDigit;

public:

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

