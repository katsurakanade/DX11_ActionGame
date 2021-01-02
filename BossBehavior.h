/*
�{�X�s�׃N���X
*/
#pragma once

#include "EnemyBehavior.h"

enum class BEHAVIOR_STATE_BOSS {
	Idle, // �ҋ@
	Chase, // �ǐ�
	Attack, // �U��
	Magic, // ���@
	Summon, // ����
	Dying, // ���S
};

class BossBehavior : public EnemyBehavior
{

private:

	// �X�e�[�g�}�b�v
	std::map <BEHAVIOR_STATE_BOSS, std::string> mStatemap;
	// �X�^�[�g
	bool mStart;
	
	// �����֘A -----------------------------
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
	// �����\���G�̍��W
	D3DXVECTOR3 mSummonenemyPos;
	// �������@�w�G�t�F�N�g
	Sprite* mSummonSprite;
	// -------------------------------------

	// ���@�U���֘A ----------------------
	float mSpellTimeMagic;
	bool mUsedMagic;
	// -------------------------------------

	float mCoolSkill;

	// �X�L���g���\
	bool mCanUseSkill;
	// ���S
	bool mDead;

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

