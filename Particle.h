/*
パーティクルクラス
*/

#pragma once

#include "Resource.h"

// 最大数
//#define MAX_PARTICLE 50000

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

// パーティクル数値設定用
struct ParitcleSetting {
	// 数
	int Amount = 50000;
	// ランダム速度フラグ
	bool RandomSpeed = true;
	// 座標
	D3DXVECTOR3 Position = D3DXVECTOR3(0,0,0);
	// 座標最小最大(ランダム)
	D3DXVECTOR2 PostionMinMaxX = D3DXVECTOR2(0,0);
	D3DXVECTOR2 PostionMinMaxY = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 PostionMinMaxZ = D3DXVECTOR2(0, 0);
	// 速度(直接設定)
	D3DXVECTOR3 Speed = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	// 速度最小最大XYZ(ランダム)
	D3DXVECTOR2 SpeedMinMaxX = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 SpeedMinMaxY = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 SpeedMinMaxZ= D3DXVECTOR2(0, 0);
	// ライフ最小最大(ランダム)
	D3DXVECTOR2 LifeMinMax = D3DXVECTOR2(60, 120);
	// サイズ
	float Size = 0.1f;
};

// 時間（Compute Shader計算用）
struct TimeCompute {
	float Time;
	float DeltaTime;
};

class ParticleSystem : public Resource
{

protected:

	// ライフ
	float* mlife;
	// テクスチャ
	ID3D11ShaderResourceView* mTexture = nullptr;
	// 削除フレーム
	float mKillFrame;
	// Compute Shader用バッファ生成
	void CreateComputeResource();
	// パーティクル数
	int mParticleAmount;
	// パーティクルライブ最大値
	int mParticleLifeMax;

public:

	// パーティクル
	Particle* mparticle;
	// 速度
	D3DXVECTOR3* mVel;
	// パーティクル座標
	D3DXVECTOR3* mParticlePos;
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

	void Create(ParitcleSetting* setting);

	// Setter
	void SetTexture(ID3D11ShaderResourceView* tex) { mTexture = tex; };

	// Getter
	Particle* GetParticle() { return mparticle; };
	D3DXVECTOR3* GetVelocity() { return mVel; };
};

