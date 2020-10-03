/*
�t�B�[���h�N���X
*/

#pragma once

#include "Resource.h"

class Field : public Resource
{
private:

	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer = NULL;
	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Render();
};
