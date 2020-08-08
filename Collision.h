#pragma once

#include "Component.h"

class BoxCollider : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	D3DXVECTOR3 Size = D3DXVECTOR3(1.0f,1.0f,1.0f);

public:

	void Init();
	void Uninit();
	void Update(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Render();

	bool Collision_Box_Stay(BoxCollider* target);

};

