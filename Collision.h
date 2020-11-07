/*
�������蔻��N���X
*/

#pragma once

#include "Component.h"

class BoxCollider : public Component
{
private:

	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11Buffer* mIndexBuffer = nullptr;

	// �T�C�X
	D3DXVECTOR3 mSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// Trigger�t���O
	bool mStay = false;
	bool mTriggerFlag = false;

	// ForDebug
	void DataPanel();

public:

	// �Έڗ�
	D3DXVECTOR3 mPositionOffest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 mScaleOffest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 mScaleOffestCoff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	void Init();
	void Uninit();
	void Update();
	void Render();

	// �؍�
	bool Collision_Box_Stay(BoxCollider* target);
	// ������
	bool Collision_Box_Enter(BoxCollider* target);

	// Getter
	bool GetTrigger() { return mTriggerFlag; };
};

