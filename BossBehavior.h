/*
�{�X�s�׃N���X
*/
#pragma once

#include "EnemyBehavior.h"

enum class BEHAVIOR_STATE_BOSS {
	Idle, // �ҋ@
	Chase, // �ǐ�
	Attack, // �U��
	Summon, // ����
	Dying, // ���S
};

class BossBehavior : public EnemyBehavior
{

private:

	// �X�e�[�g�}�b�v
	std::map <BEHAVIOR_STATE_BOSS, std::string> mStatemap;

	
	// �����֘A -----------------------------

	// �N�[���^�C��
	float mCoolSummon; 
	// ��������
	bool mUsedSummon;
	// �����p�X���b�h
	std::thread mSummonThread;
	// �҂�����
	float mSummonThreadWaitTime;
	// ����
	void Summon();
	// �����X�V����
	void Summonprocess();
	// ���������G�̃|�C���^
	Enemy* mSummonenemy;

	// -------------------------------------

	// �X�L���g���\
	bool mCanUseSkill;

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

