#pragma once

#include "Resource.h"

class Field : public Resource
{
private:

	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11ShaderResourceView* mTexture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Render();
};
