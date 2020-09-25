#pragma once

#include "Resource.h"

class MeshField : public Resource
{

private:

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	ID3D11ShaderResourceView* mTexture;

	VERTEX_3D mVertex[21][21];

	void ResetField();

public:
	void Init();
	void Unint();
	void Update();
	void Render();
};

