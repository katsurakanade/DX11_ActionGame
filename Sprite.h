/*
スプライトクラス
*/
#pragma once

#include "Resource.h"

class Sprite : public Resource
{
private:

	// バッファ
	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	// テクスチャ
	ID3D11ShaderResourceView* mTexture = NULL;
	// サイス
	D3DXVECTOR3 mSize = D3DXVECTOR3(64.0f,64.0f,0.0f);

	// アニメーション用
	bool mAnimation = false;
	int mFramecount;
	std::vector <std::vector <D3DXVECTOR2>> mFrame;
	int mWidth = 3;
	int mHeight = 3;
	D3DXVECTOR2 MakeFrame();
	bool mFill = false;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetTexture(ID3D11ShaderResourceView* value);
	void SetSize(D3DXVECTOR3 value);
	void SetAnimationSprite(bool val) { mAnimation = val; };
	void SetFillSprite(bool val) { mFill = val; };
	void SetFrame(int frame) { mFramecount = frame; };
	void SetHW(int valx, int valy) { mWidth = valx; mHeight = valy; };
	void SetPosition(D3DXVECTOR3 pos);
	void SetColor(D3DXVECTOR4 col);
	// Getter
	D3DXVECTOR3 GetSize() { return mSize; };
};

