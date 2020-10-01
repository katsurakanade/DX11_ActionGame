#pragma once

#include "Resource.h"

class Camera : public Resource
{

private:

	D3DXVECTOR3 mTarget;
	Resource* mFollowTarget;
	D3DXVECTOR3 mFollowPostionOffset;
	D3DXVECTOR3 mFollowProjectionOffset;
	D3DXVECTOR3 mControllerPosition;
	D3DXVECTOR3 mControllerSavePosition;
	D3DXMATRIX mViewMatrix;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetFollowTarget(Resource* obj) { mFollowTarget = obj; };
	D3DXMATRIX GetViewMatrix() { return mViewMatrix; };
	Resource* GetFollowTarget() { return mFollowTarget; };
};

