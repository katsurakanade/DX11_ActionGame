/*
�v���b�v�N���X
*/
#pragma once

#include "Resource.h"

class ModelManager;
class BoxCollider;

class Props : public Resource
{

private:

	// ���f���|�C���^
	ModelManager* mpModel;
	// Collider�|�C���^
	BoxCollider* mpCollider;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

