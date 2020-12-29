/*
ボス行為クラス
*/
#pragma once

#include "EnemyBehavior.h"

enum class BEHAVIOR_STATE_BOSS {
	Idle, // 待機
	Chase, // 追跡
	Attack, // 攻撃
	Dying, // 死亡
};

class BossBehavior : public EnemyBehavior
{

public:
	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();
};

