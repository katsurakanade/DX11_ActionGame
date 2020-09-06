#pragma once

#include "Component.h"

// 物理クラス : リソースクラス
class Physical : public Component
{

private:

	// 速度減衰係数
	const float mSpeedDownCoefficient;
	// 移動中
	bool IsMoving();
	// 地面にいる
	bool IsGround;
	// 重力
	const float mGravity;
	// 座標処理
	void ProcessPostion();
	// データパネル
	void DataPanel();

public:

	Physical() : mSpeedDownCoefficient(0.93f) ,mGravity(9.8f) , mAcceleration(0.0f) , mSpeed(0) , IsGround(true) {};

	// 加速度
	float mAcceleration;
	// 速度
	float mSpeed;
	// 速度方向
	D3DXVECTOR3 mVelocity;
	// ジャンプ力
	D3DXVECTOR3 mForce;

	void Init();
	void Uninit();
	void Update();

	void AddForce(D3DXVECTOR3 force);

	void SpeedDown(float value) {
		mSpeed -= value;
	}

	bool GetIsGround() { return IsGround; };


};

