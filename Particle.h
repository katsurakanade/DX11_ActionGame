#pragma once

#include "Resource.h"

#define MAX_PARTICLE 10000

struct Particle {
	VERTEX_3D vertex[4];
};

struct ParticleCompute {
	D3DXVECTOR3 pos[4];
	D3DXVECTOR3 vel;
};

class ParticleSystem : public Resource
{

private:

	D3DXVECTOR3 mVel[MAX_PARTICLE];

	D3DXVECTOR3 mSize = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	ID3D11ShaderResourceView* mTexture = nullptr;

	bool start = false;

	void CreateComputeResource();

public:

	Particle mparticle[MAX_PARTICLE];
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mColorBuffer;

	ID3D11Buffer* mpParticleBuffer;
	ID3D11Buffer* mpVelBuffer;
	ID3D11Buffer* mpResultBuffer;
	ID3D11ShaderResourceView* mpParticleSRV;
	ID3D11ShaderResourceView* mpVelSRV;
	ID3D11UnorderedAccessView* mpResultUAV;

	void Init();
	void Uninit();
	void Update();
	void Render();
};

