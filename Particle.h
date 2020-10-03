/*
パーティクルクラス
*/

#pragma once

#include "Resource.h"

// 最大数
#define MAX_PARTICLE 100000

// パーティクル
struct Particle {
	VERTEX_3D vertex[4];
};

// パーティクル（Compute Shader計算用）
struct ParticleCompute {
	// 座標
	D3DXVECTOR3 pos[4];
	// 速度
	D3DXVECTOR3 vel;
	// カラー
	D3DXVECTOR4 col;
	// ライフ
	float life;
};

// 時間（Compute Shader計算用）
struct TimeCompute {
	float Time;
	float DeltaTime;
};

class ParticleSystem : public Resource
{

protected:

	// 速度
	D3DXVECTOR3 mVel[MAX_PARTICLE];
	// ライフ
	float mlife[MAX_PARTICLE];
	// サイス
	D3DXVECTOR3 mSize = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	// テクスチャ
	ID3D11ShaderResourceView* mTexture = nullptr;
	// 削除フレーム
	float mKillFrame;
	// Compute Shader用バッファ生成
	void CreateComputeResource();

public:

	// パーティクル
	Particle* mparticle;
	// バッファ
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

