/*
�p�[�e�B�N���N���X
*/

#pragma once

#include "Resource.h"

// �ő吔
#define MAX_PARTICLE 100000

// �p�[�e�B�N��
struct Particle {
	VERTEX_3D vertex[4];
};

// �p�[�e�B�N���iCompute Shader�v�Z�p�j
struct ParticleCompute {
	// ���W
	D3DXVECTOR3 pos[4];
	// ���x
	D3DXVECTOR3 vel;
	// �J���[
	D3DXVECTOR4 col;
	// ���C�t
	float life;
};

// ���ԁiCompute Shader�v�Z�p�j
struct TimeCompute {
	float Time;
	float DeltaTime;
};

class ParticleSystem : public Resource
{

protected:

	// ���x
	D3DXVECTOR3 mVel[MAX_PARTICLE];
	// ���C�t
	float mlife[MAX_PARTICLE];
	// �T�C�X
	D3DXVECTOR3 mSize = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = nullptr;
	// �폜�t���[��
	float mKillFrame;
	// Compute Shader�p�o�b�t�@����
	void CreateComputeResource();

public:

	// �p�[�e�B�N��
	Particle* mparticle;
	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mpParticleBuffer;
	ID3D11Buffer* mpTimeBuffer;
	ID3D11Buffer* mpResultBuffer;
	// SRV
	ID3D11ShaderResourceView* mpParticleSRV;
	ID3D11ShaderResourceView* mpTimeSRV;
	// UAV
	ID3D11UnorderedAccessView* mpResultUAV;

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetTexture(ID3D11ShaderResourceView* tex) { mTexture = tex; };
};

