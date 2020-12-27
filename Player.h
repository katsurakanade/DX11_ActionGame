/*
�v���C���[�N���X
*/

#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;
class BoxCollider;
class PlayerBehavior;

class Player : public Resource
{

private:

	// HP
	float mHpInit = 40000.0f;
	// ForDebug
	void SettingPanel();
	// �R���|�[�l���g
	Animation* mpAnination;
	ModelManager* mpModel;
	Physical* mpPhysical;
	BoxCollider* mpCollider;
	PlayerBehavior* mpPlayerBehavior;
	// ���C���J�����|�C���^
	Camera* mpCamera;

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

