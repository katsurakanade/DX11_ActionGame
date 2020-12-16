/*
�p�[�e�B�N���N���X
*/

#pragma once

#include "Resource.h"

// �p�[�e�B�N���p���_���C�A�E�g�i�@���A���C�g�����j
struct VERTEX_3D_PARTICLE
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 TexCoord;
};

// �p�[�e�B�N���iCompute Shader�v�Z�p�j
struct ParticleCompute {
	// ���W
	D3DXVECTOR3 pos;
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
	// �����_�����x
	bool RandomSpeed = true;
	// �ɍ��W
	bool PolarCoordinates = false;
	// ���W
	D3DXVECTOR3 Position = D3DXVECTOR3(0, 0, 0);
	// ���W�ŏ��ő�(�����_��)
	D3DXVECTOR2 PostionMinMaxX = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 PostionMinMaxY = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 PostionMinMaxZ = D3DXVECTOR2(0, 0);
	// ���x(���ڐݒ�)
	D3DXVECTOR3 Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���x�ŏ��ő�XYZ(�����_��)
	D3DXVECTOR2 SpeedMinMaxX = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 SpeedMinMaxY = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 SpeedMinMaxZ = D3DXVECTOR2(0, 0);
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

	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = nullptr;
	// �폜�t���[��
	float mKillFrame;
	// Compute Shader�p�o�b�t�@�ASRV�AUAV����
	void CreateComputeResource();
	// �p�[�e�B�N����
	int mParticleAmount;
	// �p�[�e�B�N�����C�u�ő�l
	int mParticleLifeMax;

public:

	// �p�[�e�B�N��
	ParticleCompute* mparticle;
	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mpParticleBuffer;
	ID3D11Buffer* mpTimeBuffer;
	ID3D11Buffer* mpResultBuffer;
	ID3D11Buffer* mpPositionBuffer;
	ID3D11Buffer* mpLifeBuffer;
	// SRV
	ID3D11ShaderResourceView* mpParticleSRV;
	ID3D11ShaderResourceView* mpTimeSRV;
	ID3D11ShaderResourceView* mpPositionSRV;
	ID3D11ShaderResourceView* mpLifeSRV;
	// UAV
	ID3D11UnorderedAccessView* mpResultUAV;

	void Init();
	void Uninit();
	void Update();
	void Render();

	// �p�[�e�B�N����������
	void Create(ParitcleSetting* setting);

	// Setter
	void SetTexture(ID3D11ShaderResourceView* tex) { mTexture = tex; };

};

