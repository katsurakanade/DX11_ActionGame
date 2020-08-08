#pragma once

#include "Resource.h"

class Field : public Resource
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView* m_ToonTexture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Render();
};
