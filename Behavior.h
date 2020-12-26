/*
�s�׃N���X
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

class Behavior : public Component
{

private:

	// �X�e�[�g
	BEHAVIOR_STATE mState;
	// �R���|�[�l���g
	Physical* mpPhysical;
	Animation* mpAnimation;
	// �v���C���[�|�C���^
	Player* mpPlayer;
	// �ړ�
	void Movement(int arrow);
	// �ꏊ�Ɉړ�
	void MoveTo(D3DXVECTOR3 target_position);

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

};

