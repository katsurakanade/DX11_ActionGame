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

	float mMaxSpeedChase;
	float mPlusSpeedChase;

	// 移動
	void Movement(int arrow);
	// 指定場所に移動
	void MoveTo(D3DXVECTOR3 target_position);
	// 向き
	void LookAt(D3DXVECTOR3 target_position);
	// 死亡処理
	void Dying();
	// ステート
	std::string mState;

	// 行動決め
	virtual void ChooseAction() = 0;
	// 行動実行
	virtual void RunAction() = 0;

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

