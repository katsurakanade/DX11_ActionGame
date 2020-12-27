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
};

class EnemyBehavior : public Component
{

private:

	// �R���|�[�l���g
	Physical* mpPhysical;
	Animation* mpAnimation;
	// �v���C���[�|�C���^
	Player* mpPlayer;
	// �v���C���[�Ƃ̋���
	float mLengthToPlayer;

	// �ړ�
	void Movement(int arrow);
	// �ꏊ�Ɉړ�
	void MoveTo(D3DXVECTOR3 target_position);

	// �X�e�[�g
	std::string mState;
	// �X�e�[�g�}�b�v
	std::map <BEHAVIOR_STATE, std::string> mStatemap;

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();

};

