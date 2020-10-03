/*
�X�J�C�{�b�N�X�N���X
*/
#pragma once

#include "AssimpModel.h"
#include "Resource.h"

class Skybox :public Resource
{

private:
	
	// ���f��
	AssimpModel* mModel;
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

