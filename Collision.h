#pragma once

#include "Component.h"

class BoxCollider : public Component
{
private:

	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mIndexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	D3DXVECTOR3 mSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	bool mStay = false;
	bool mTriggerFlag = false;

public:

	D3DXVECTOR3 mPositionOffest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 mScaleOffest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	void Init();
	void Uninit();
	void Update(Resource* target);
	void Render();

	bool Collision_Box_Stay(BoxCollider* target);
	bool Collision_Box_Enter(BoxCollider* target);

	bool GetTrigger() { return mTriggerFlag; };
};

