/*
ビルボードクラス
*/

#pragma once

#include "Resource.h"

class Grass : public Resource
{
private:

	// バッファ
	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	// テクスチャ
	ID3D11ShaderResourceView* mTexture = NULL;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
	
	// Setter
	void SetTexture(ID3D11ShaderResourceView* value) { mTexture = value; };

};

