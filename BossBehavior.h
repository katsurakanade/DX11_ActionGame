/*
�{�X�s�׃N���X
*/
#pragma once

#include "EnemyBehavior.h"

enum class BEHAVIOR_STATE_BOSS {
	Idle, // �ҋ@
	Chase, // �ǐ�
	Attack, // �U��
	Dying, // ���S
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

