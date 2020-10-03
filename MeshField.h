/*
���b�V���t�B�[���h�N���X
*/

#pragma once

#include "Resource.h"

class MeshField : public Resource
{

private:

	// �}�b�v
	static float HeightMap[21][21];
	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	// �e�N�X�`��
	std::vector <ID3D11ShaderResourceView*> mTexture;
	// ���_
	VERTEX_3D mVertex[21][21];
	// ���Z�b�g
	void ResetField();

public:

	void Init();
	void Unint();
	void Update();
	void Render();

	// Getter
	float GetHeight(D3DXVECTOR3 pos);
};

