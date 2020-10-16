/*
�p�[�e�B�N���N���X
*/

#pragma once

#include "Resource.h"

// �ő吔
//#define MAX_PARTICLE 50000

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

// �p�[�e�B�N�����l�ݒ�p
struct ParitcleSetting {
	// ��
	int Amount = 50000;
	// �����_�����x�t���O
	bool RandomSpeed = true;
	// ���W
	D3DXVECTOR3 Position = D3DXVECTOR3(0,0,0);
	// ���W�ŏ��ő�(�����_��)
	D3DXVECTOR2 PostionMinMaxX = D3DXVECTOR2(0,0);
	D3DXVECTOR2 PostionMinMaxY = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 PostionMinMaxZ = D3DXVECTOR2(0, 0);
	// ���x(���ڐݒ�)
	D3DXVECTOR3 Speed = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	// ���x�ŏ��ő�XYZ(�����_��)
	D3DXVECTOR2 SpeedMinMaxX = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 SpeedMinMaxY = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 SpeedMinMaxZ= D3DXVECTOR2(0, 0);
	// ���C�t�ŏ��ő�(�����_��)
	D3DXVECTOR2 LifeMinMax = D3DXVECTOR2(60, 120);
	// �T�C�Y
	float Size = 0.1f;
};

// ���ԁiCompute Shader�v�Z�p�j
struct TimeCompute {
	float Time;
	float DeltaTime;
};

class ParticleSystem : public Resource
{

protected:

	// ���C�t
	float* mlife;
	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = nullptr;
	// �폜�t���[��
	float mKillFrame;
	// Compute Shader�p�o�b�t�@����
	void CreateComputeResource();
	// �p�[�e�B�N����
	int mParticleAmount;
	// �p�[�e�B�N�����C�u�ő�l
	int mParticleLifeMax;

public:

	// �p�[�e�B�N��
	Particle* mparticle;
	// ���x
	D3DXVECTOR3* mVel;
	// �p�[�e�B�N�����W
	D3DXVECTOR3* mParticlePos;
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

	void Create(ParitcleSetting* setting);

	// Setter
	void SetTexture(ID3D11ShaderResourceView* tex) { mTexture = tex; };

	// Getter
	Particle* GetParticle() { return mparticle; };
	D3DXVECTOR3* GetVelocity() { return mVel; };
};

