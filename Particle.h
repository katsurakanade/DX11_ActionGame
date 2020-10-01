#pragma once

#include "Resource.h"

#define MAX_PARTICLE 50000

struct Particle {
	VERTEX_3D vertex[4];
};

struct ParticleCompute {
	D3DXVECTOR3 pos[4];
	D3DXVECTOR3 vel;
	float life;
};

class ParticleSystem : public Resource
{

protected:

	D3DXVECTOR3 mVel[MAX_PARTICLE];
	float mlife[MAX_PARTICLE];

	D3DXVECTOR3 mSize = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	ID3D11ShaderResourceView* mTexture = nullptr;

	bool start = false;
	float mKillFrame;

	void CreateComputeResource();

public:

	Particle* mparticle;
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mpParticleBuffer;
	ID3D11Buffer* mpResultBuffer;
	ID3D11ShaderResourceView* mpParticleSRV;
	ID3D11UnorderedAccessView* mpResultUAV;

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetTexture(ID3D11ShaderResourceView* tex) { mTexture = tex; };
};

