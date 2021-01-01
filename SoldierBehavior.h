/*
一般敵行為クラス
*/
#pragma once

#include "EnemyBehavior.h"

// ステート
enum class BEHAVIOR_STATE_SOLDIER {
	Idle, // 待機
	Chase, // 追跡
	Attack, // 攻撃
	Dying, // 死亡
};

class SoldierBehavior : public EnemyBehavior
{
private:
	
	// ステートマップ
	std::map <BEHAVIOR_STATE_SOLDIER, std::string> mStatemap;
	// 攻撃待ちタイム
	float mAttackWaitTime;

protected:

	// 行動決め
	void ChooseAction();
	// 行動実行
	void RunAction();

public:
	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();
};

