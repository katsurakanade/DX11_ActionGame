/*
�G�N���X
*/
#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Animation;

class Enemy : public Resource
{

private:

	// ���f��
	AssimpModel* mModel;
	// HP
	float mHpInit;
	float mHp;
	// �Q�[�W
	Gauge* mGauge;
	// �A�j���[�V�����|�C���^
	Animation* mpAnination;
	// �����n�߂�
	bool mStart;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// �Q�[�W�ǉ�
	void AddGauge();
	// �U��
	void Attack();
	// �ړ�
	void Movement(int arrow);
	// ����
	void LookAt();
};

