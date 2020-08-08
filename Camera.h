#pragma once

#include "Resource.h"

class Camera : public Resource
{

private:

	D3DXVECTOR3 Target;
	Resource* FollowTarget;
	D3DXVECTOR3 FollowPostionOffset;
	D3DXVECTOR3 FollowProjectionOffset;
	D3DXMATRIX viewMatrix;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetFollowTarget(Resource* obj) { FollowTarget = obj; };
	D3DXMATRIX GetviewMatrix() { return viewMatrix; };
};

