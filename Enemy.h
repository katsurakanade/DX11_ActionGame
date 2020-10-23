/*
敵クラス
*/
#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Animation;
class ModelManager;

class Enemy : public Resource
{

private:

	
	// HP初期
	float mHpInit;
	// ゲージ
	Gauge* mGauge;
	// アニメーションポインタ
	Animation* mpAnination;
	ModelManager* mpModel;
	// ロック画像
	Sprite* mpLockImage;
	// 動き始める
	bool mStart;

public:

	// ロック
	bool Is_Lock = false;
	// HP
	float mHp;

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

