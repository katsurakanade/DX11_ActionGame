#pragma once

#include "Resource.h"

class Sprite : public Resource
{
private:

	ID3D11Buffer* VertexBuffer = NULL;
	ID3D11ShaderResourceView* Texture = NULL;
	D3DXVECTOR3 Size = D3DXVECTOR3(300.0f,150.0f,0.0f);

public:
	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetTexture(ID3D11ShaderResourceView* value);
	void SetSize(D3DXVECTOR3 value) { Size = value; };
};

