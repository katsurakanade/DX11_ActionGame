/*
�v���b�v�N���X
*/
#pragma once

#include "Resource.h"

class ModelManager;

class Props : public Resource
{

private:

	// ���f���|�C���^
	ModelManager* mpModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
};

