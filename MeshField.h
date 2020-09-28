#pragma once

#include "Resource.h"

class MeshField : public Resource
{

private:

	static float HeightMap[21][21];
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	std::vector <ID3D11ShaderResourceView*> mTexture;

	VERTEX_3D mVertex[21][21];

	void ResetField();

public:
	void Init();
	void Unint();
	void Update();
	void Render();

	float GetHeight(D3DXVECTOR3 pos);
};

