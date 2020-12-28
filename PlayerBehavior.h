/*
�v���C���[�s�׃N���X
*/
#pragma once
#include "Component.h"

class BoxCollider;
class Physical;
class Animation;
class ModelManager;

class PlayerBehavior : public Component
{

private:

	// �R���|�[�l���g
	Physical* mpPhysical;
	Animation* mpAnimation;
	BoxCollider* mpCollider;
	ModelManager* mpModelManager;

	// ���C���J�����|�C���^
	Camera* mpCamera;

	// �L�����^�C�v
	int mCharacterType;
	// ���b�N���Ă���G�C���f�b�N�X
	unsigned int mLockIndex;

	// �ړ�
	void Movement(BYTE keycodeF, BYTE keycodeB, BYTE keycodeR, BYTE keycodeL);
	// �X�L��
	void Skill(BYTE keycode_0, BYTE keycode_1, BYTE keycode_2, BYTE keycode_3);
	// �L�����N�^�[�ؑ�
	void SwitchCharacter(BYTE keycode_prev, BYTE keycode_next);
	// �ڕW���b�N
	void LockTarget(BYTE keycode_lock);


public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();
};

