/*
�X�J�C�{�b�N�X�N���X
*/
#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class ModelManager;

class Skybox :public Resource
{

private:

	// ���f���|�C���^
	ModelManager* mpModel;
	// �e�N�X�`���C���f�b�N�X
	int TexutreIndex = 4;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetModelTexture(int val) {
		TexutreIndex = val;
	}
};

