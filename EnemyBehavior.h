/*
�G�s�׃N���X
*/
#pragma once
#include "Component.h"

class Physical;
class Animation;
class Player;

class EnemyBehavior : public Component
{

protected:

	// �R���|�[�l���g
	Physical* mpPhysical;
	Animation* mpAnimation;
	// �v���C���[�|�C���^
	Player* mpPlayer;
	// �v���C���[�Ƃ̋���
	float mLengthToPlayer;
	// ���S�^�C�}�[
	float mDeadTimer;

	float mMaxSpeedChase;
	float mPlusSpeedChase;

	// �ړ�
	void Movement(int arrow);
	// �w��ꏊ�Ɉړ�
	void MoveTo(D3DXVECTOR3 target_position);
	// ����
	void LookAt(D3DXVECTOR3 target_position);
	// ���S����
	void Dying();
	// �X�e�[�g
	std::string mState;

	// �s������
	virtual void ChooseAction() = 0;
	// �s�����s
	virtual void RunAction() = 0;

public:

	// HP����
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

