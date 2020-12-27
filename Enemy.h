/*
敵クラス
*/
#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Animation;
class ModelManager;
class BoxCollider;
class Physical;
class EnemyBehavior;

class Enemy : public Resource
{

private:

	
	// HP初期
	float mHpInit;
	// ゲージ
	Gauge* mGauge;
	// コンポーネント
	Animation* mpAnination;
	ModelManager* mpModel;
	Physical* mpPhysical;
	BoxCollider* mpCollider;
	EnemyBehavior* mpBehavior;
	// ロック画像
	Sprite* mpLockImage;

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
	
};
