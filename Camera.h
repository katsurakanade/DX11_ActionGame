/*
カメラクラス
*/

#pragma once

#include "Resource.h"

class Camera : public Resource
{

private:

	// ID
	static int ID;

	// 視点
	D3DXVECTOR3 mTarget;
	// 追跡ターゲット
	Resource* mFollowTarget;
	Resource* mLookTarget;

	// 偏移
	D3DXVECTOR3 mFollowPostionOffset;
	D3DXVECTOR3 mFollowProjectionOffset;
	D3DXVECTOR3 mControllerPosition;
	D3DXVECTOR3 mControllerSavePosition;

	// マトリックス
	D3DXMATRIX mViewMatrix;

public:

	Camera() : mFollowTarget(nullptr), mLookTarget(nullptr) { ID++; };
	~Camera() { ID--; };

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetFollowTarget(Resource* obj) { mFollowTarget = obj; };
	void SetLookTarget(Resource* obj) { mLookTarget = obj; };
	void SetFollowPostionOffset(D3DXVECTOR3 value) { mFollowPostionOffset = value; };
	void SetControllerPosition(D3DXVECTOR3 value) { mControllerPosition = value; };
	void AddControllerPosition(D3DXVECTOR3 value) { mControllerPosition += value; };

	// Getter
	D3DXMATRIX GetViewMatrix() { return mViewMatrix; };
	Resource* GetFollowTarget() { return mFollowTarget; };
	Resource* GetLookTarget() { return mLookTarget; };
};

