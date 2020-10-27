/*
�v���C���[�N���X
*/

#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;
class BoxCollider;

class Player : public Resource
{

private:

	// HP
	float mHpInit = 40000.0f;
	// �L�����^�C�v
	int mCharacterType;
	// ForDebug
	void SettingPanel();
	// �ړ�
	void Movement(BYTE keykodeF, BYTE keykodeB,BYTE keykodeR, BYTE keykodeL);
	// �X�L��
	void Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3);
	// �R���|�[�l���g
	Animation* mpAnination;
	ModelManager* mpModel;
	Physical* mpPhysical;
	BoxCollider* mpCollider;
	// ���C���J�����|�C���^
	Camera* mpCamera;
	// ���b�N���Ă���G�C���f�b�N�X
	unsigned int mLockIndex;

public:

	// HP
	float mHp;

	void Init();
	void Unint();
	void Update();
	void Render();

	// Getter
	float GetHpInit(){ return mHpInit; };
};

