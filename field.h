/*
フィールドクラス
*/

#pragma once

#include "Resource.h"

class Field : public Resource
{
private:

	// バッファ
	ID3D11Buffer* mVertexBuffer = NULL;
	// テクスチャ
	ID3D11ShaderResourceView* mTexture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Render();
};
