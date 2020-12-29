/*
敵行為クラス
*/
#pragma once
#include "Component.h"

class Physical;
class Animation;
class Player;

class EnemyBehavior : public Component
{

protected:

	// コンポーネント
	Physical* mpPhysical;
	Animation* mpAnimation;
	// プレイヤーポインタ
	Player* mpPlayer;
	// プレイヤーとの距離
	float mLengthToPlayer;
	// 死亡タイマー
	float mDeadTimer;
	// 移動
	void Movement(int arrow);
	// 場所に移動
	void MoveTo(D3DXVECTOR3 target_position);
	// 死亡処理
	void Dying();
	// ステート
	std::string mState;

public:

	// HP初期
	float mHpInit;
	// HP
	float mHp;

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void DataPanel();

	// Getter
	float GetLengthToPlayer() { return mLengthToPlayer; };
};

