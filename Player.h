/*
�v���C���[�N���X
*/

#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;

class Player : public Resource
{

private:

	// HP
	float mHpInit = 40000.0f;
	// �A�j���[�V�������x
	float mAnimationSpeed = 3.0f;
	// �A�j���[�V�������
	std::string mAnimationState = "Idle";
	// ���f��
	AssimpModel* mModel;
	// ForDebug
	void SettingPanel();

	//void Jump(BYTE keykode);
	// �ړ�
	void Movement(BYTE keykodeF, BYTE keykodeB,BYTE keykodeR, BYTE keykodeL);
	// �X�L��
	void Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3);
	// �A�j���[�V�����|�C���^
	Animation* mpAnination;

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

