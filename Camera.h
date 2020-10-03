/*
カメラクラス
*/

#pragma once

#include "Resource.h"

class Camera : public Resource
{

private:

	// 視点
	D3DXVECTOR3 mTarget;
	// 追跡ターゲット
	Resource* mFollowTarget;

	// 偏移
	D3DXVECTOR3 mFollowPostionOffset;
	D3DXVECTOR3 mFollowProjectionOffset;
	D3DXVECTOR3 mControllerPosition;
	D3DXVECTOR3 mControllerSavePosition;

	// マトリックス
	D3DXMATRIX mViewMatrix;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetFollowTarget(Resource* obj) { mFollowTarget = obj; };
	// Getter
	D3DXMATRIX GetViewMatrix() { return mViewMatrix; };
	Resource* GetFollowTarget() { return mFollowTarget; };
};

