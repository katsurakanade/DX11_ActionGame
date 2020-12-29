/*
�G�s�׃N���X
*/
#pragma once
#include "Component.h"

class Physical;
class Animation;
class Player;

// �X�e�[�g
enum class BEHAVIOR_STATE{
	Idle, // �ҋ@
	Chase, // �ǐ�
	Attack, // �U��
	Dying, // ���S
};

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

	// �ړ�
	void Movement(int arrow);
	// �ꏊ�Ɉړ�
	void MoveTo(D3DXVECTOR3 target_position);
	// ���S����
	void Dying();

	// �X�e�[�g
	std::string mState;
	// �X�e�[�g�}�b�v
	std::map <BEHAVIOR_STATE, std::string> mStatemap;

public:

	// HP����
	float mHpInit;
	// HP
	float mHp;

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();

	// Getter
	float GetLengthToPlayer() { return mLengthToPlayer; };
};

