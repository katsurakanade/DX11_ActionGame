#pragma once

#include "Resource.h"

struct Particle
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Col;
	float vel;
	bool active;
};

class ParticleSystem : public Resource
{

private:

	ID3D11ShaderResourceView* Texture = NULL;

	Particle* m_particlelist;

	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;

	int m_currentParticleCount;
	float m_accumulatedTime;

	int m_vertexCount, m_indexCount;
	VERTEX_3D* m_vertices;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

};

