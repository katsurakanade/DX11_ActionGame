#pragma once

#include "Resource.h"

#define MAX_PARTICLE 1024

struct Particle {
	VERTEX_3D vertex[4];
};

class ParticleSystem : public Resource
{

private:

	Particle mparticle[MAX_PARTICLE];

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mColorBuffer;

	D3DXVECTOR3 mSize = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	ID3D11ShaderResourceView* mTexture = nullptr;

	bool start = false;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

