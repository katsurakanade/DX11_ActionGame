/*
�v���b�v�N���X
*/
#pragma once

#include "Resource.h"

class Props : public Resource
{
	// ���f��
	AssimpModel* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetModel(AssimpModel* model) { mModel = model; };
};

