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
class EnemyBehavior;

class Enemy : public Resource
{

private:

	// �Q�[�W
	Gauge* mGauge;
	// �R���|�[�l���g
	Animation* mpAnination;
	ModelManager* mpModel;
	Physical* mpPhysical;
	BoxCollider* mpCollider;
	EnemyBehavior* mpBehavior;
	// ���b�N�摜
	Sprite* mpLockImage;

public:

	// ���b�N
	bool Is_Lock = false;

	void Init();
	void Uninit();
	void Update();
	void Render();

	void Create();

	// �Q�[�W�ǉ�
	void AddGauge(D3DXVECTOR3 offset);
	
};
