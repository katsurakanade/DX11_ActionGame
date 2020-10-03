/*
エフェクトクラス
*/

#pragma once
#include "Resource.h"

// デフォルトフレーム
#define EFFECT_X_DEFAULT 4
#define EFFECT_Y_DEFAULT 4

class Effect : public Resource
{
private:

	// バッファ
	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	// テクスチャ
	ID3D11ShaderResourceView* mTexture = NULL;
	// サイズ
	D3DXVECTOR3 mSize = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	// フレーム数
	int mFramecount;
	// フレーム
	std::vector <std::vector <D3DXVECTOR2>> mFrame;

	// 横縦
	int mWidth = EFFECT_X_DEFAULT;
	int mHeight = EFFECT_Y_DEFAULT;

	// 速度調整用
	float mWaitframe;
	float mAnimeSpeed = 1.0f;
	bool mLoop = false;

	// フレーム生成
	D3DXVECTOR2 MakeFrame();

	// フィル
	float mFillAmount = 1.0f;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetHW(int valx,int valy) { mWidth = valx; mHeight = valy; };
	void SetTexture(ID3D11ShaderResourceView* value) { mTexture = value; };
	void SetLoop(bool val) { mLoop = val; };
	void SetFillAmount(float val) { mFillAmount = val; };
	void SetAnimeSpeed(float val) { mAnimeSpeed = val; };
};

