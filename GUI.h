/*
GUIクラス
*/
#pragma once

#include "Resource.h"
#include "Gauge.h"
#include "Digit.h"
#include "ImageManager.h"

class GUI : public Resource
{
private:

	// オブジェクトポインタ
	Player* mpPlayer;
	Gauge* mpPlayerHP;
	Digit* mpPlayerHPDigit;
	Sprite* mpPlayerIcon;

public:

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

	void SetPlayerIcon(ID3D11ShaderResourceView* resource) { mpPlayerIcon->GetImage()->SetTexture(resource); };

};

