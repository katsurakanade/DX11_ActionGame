/*
�G�N���X
*/
#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Gauge.h"

class Animation;
class ModelManager;
class BoxCollider;
class Physical;

class Enemy : public Resource
{

private:

	
	// HP����
	float mHpInit;
	// �Q�[�W
	Gauge* mGauge;
	// �R���|�[�l���g
	Animation* mpAnination;
	ModelManager* mpModel;
	Physical* mpPhysical;
	BoxCollider* mpCollider;
	// ���b�N�摜
	Sprite* mpLockImage;
	// �����n�߂�
	bool mStart;

public:

	// ���b�N
	bool Is_Lock = false;
	// HP
	float mHp;

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

