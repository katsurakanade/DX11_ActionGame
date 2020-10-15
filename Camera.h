/*
�J�����N���X
*/

#pragma once

#include "Resource.h"

class Camera : public Resource
{

private:

	// ���_
	D3DXVECTOR3 mTarget;
	// �ǐՃ^�[�Q�b�g
	Resource* mFollowTarget;
	Resource* mLookTarget;

	// �Έ�
	D3DXVECTOR3 mFollowPostionOffset;
	D3DXVECTOR3 mFollowProjectionOffset;
	D3DXVECTOR3 mControllerPosition;
	D3DXVECTOR3 mControllerSavePosition;

	// �}�g���b�N�X
	D3DXMATRIX mViewMatrix;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetFollowTarget(Resource* obj) { mFollowTarget = obj; };
	void SetLookTarget(Resource* obj) { mLookTarget = obj; };
	// Getter
	D3DXMATRIX GetViewMatrix() { return mViewMatrix; };
	Resource* GetFollowTarget() { return mFollowTarget; };
	Resource* GetLookTarget() { return mLookTarget; };
};

