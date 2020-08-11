#pragma once

#include "AssimpModel.h"
#include "Resource.h"
#include "Collision.h"

class Wall : public Resource
{
private:

	AssimpModel* mModel = nullptr;
	D3DXVECTOR3 mFront;
	
public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetFront(D3DXVECTOR3 front) { this->mFront = front; };
	D3DXVECTOR3 GetFront() { return mFront; };

	void ResetPositionOffest() { 
		GetComponent<BoxCollider>()->mPositionOffest.y = (Scale.y / 2); 
		GetComponent<BoxCollider>()->mPositionOffest.x = 0;
		GetComponent<BoxCollider>()->mPositionOffest.z = 0;
	};
};

