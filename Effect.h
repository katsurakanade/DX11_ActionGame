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
	D3DXVECTOR3 mSize = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	int mFramecount;
	std::vector <std::vector <D3DXVECTOR2>> mFrame;

	int mWidth = EFFECT_X_DEFAULT;
	int mHeight = EFFECT_Y_DEFAULT;
	float mWaitframe;

	D3DXVECTOR2 MakeFrame();

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetHW(int valx,int valy) { mWidth = valx; mHeight = valy; };

};

