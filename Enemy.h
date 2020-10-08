/*
敵クラス
*/
#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Animation;

class Enemy : public Resource
{

private:

	// モデル
	AssimpModel* mModel;
	// HP
	float mHpInit;
	float mHp;
	// ゲージ
	Gauge* mGauge;
	// アニメーションポインタ
	Animation* mpAnination;
	// 動き始める
	bool mStart;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// ゲージ追加
	void AddGauge();
	// 攻撃
	void Attack();
	// 移動
	void Movement(int arrow);
	// 向き
	void LookAt();
};

