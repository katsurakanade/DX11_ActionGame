/*
フェイドクラス
*/
#pragma once

#include "Resource.h"
#include "Sprite.h"

class Fade : public Resource
{

private:

	// 画像
	Sprite* mSprite;
	// カラー
	D3DXCOLOR mFadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	// 設定
	float mAlpha = 0.0f;
	float mAddAlpha = 0.0f;
	bool mbOut = false;
	bool mIsFade = false;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// スタート
	void Start(bool bOut, int frame, D3DCOLOR color);
	// Getter
	bool GetIsFade() { return mIsFade; };

};

