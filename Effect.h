#pragma once
#include "Resource.h"

#define EFFECT_X_DEFAULT 4
#define EFFECT_Y_DEFAULT 4

class Effect : public Resource
{
private:

	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	ID3D11ShaderResourceView* mTexture = NULL;
	D3DXVECTOR3 mSize = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	int mFramecount;
	std::vector <std::vector <D3DXVECTOR2>> mFrame;

	int mWidth = EFFECT_X_DEFAULT;
	int mHeight = EFFECT_Y_DEFAULT;
	float mWaitframe;
	float mAnimeSpeed = 1.0f;
	bool mLoop = false;

	D3DXVECTOR2 MakeFrame();

	float mFillAmount = 1.0f;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetHW(int valx,int valy) { mWidth = valx; mHeight = valy; };
	void SetTexture(ID3D11ShaderResourceView* value) { mTexture = value; };
	void SetLoop(bool val) { mLoop = val; };
	void SetFillAmount(float val) { mFillAmount = val; };
	void SetAnimeSpeed(float val) { mAnimeSpeed = val; };
};

