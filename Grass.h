/*
�r���{�[�h�N���X
*/

#pragma once

#include "Resource.h"

class Grass : public Resource
{
private:

	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = NULL;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();
	
	// Setter
	void SetTexture(ID3D11ShaderResourceView* value) { mTexture = value; };

};

