#pragma once

#include "Resource.h"
#include "Sprite.h"

class Fade : public Resource
{

private:

	Sprite* mSprite;
	D3DXCOLOR mFadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	float mAlpha = 0.0f;
	float mAddAlpha = 0.0f;
	bool mbOut = false;
	bool mIsFade = false;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void Start(bool bOut, int frame, D3DCOLOR color);
	bool GetIsFade() { return mIsFade; };

};

