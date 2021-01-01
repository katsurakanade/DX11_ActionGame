/*
��ʓG�s�׃N���X
*/
#pragma once

#include "EnemyBehavior.h"

// �X�e�[�g
enum class BEHAVIOR_STATE_SOLDIER {
	Idle, // �ҋ@
	Chase, // �ǐ�
	Attack, // �U��
	Dying, // ���S
};

class SoldierBehavior : public EnemyBehavior
{
private:
	
	// �X�e�[�g�}�b�v
	std::map <BEHAVIOR_STATE_SOLDIER, std::string> mStatemap;
	// �U���҂��^�C��
	float mAttackWaitTime;

protected:

	// �s������
	void ChooseAction();
	// �s�����s
	void RunAction();

public:
	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();
};

