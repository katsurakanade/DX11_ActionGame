#pragma once

#include "Resource.h"

class Grass : public Resource
{
private:

	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	ID3D11ShaderResourceView* mTexture = NULL;
	D3DXVECTOR3 mSize = D3DXVECTOR3(300.0f, 300.0f, 0.0f);

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
	void SetTexture(ID3D11ShaderResourceView* value) { mTexture = value; };

};

