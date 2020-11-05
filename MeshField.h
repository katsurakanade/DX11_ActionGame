/*
���b�V���t�B�[���h�N���X
*/

#pragma once

#include "Resource.h"


class MeshField : public Resource
{

private:

	// �}�b�v
	static float HeightMap[FIELD_X][FIELD_X];
	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	// �e�N�X�`��
	std::vector <ID3D11ShaderResourceView*> mTexture;
	std::vector<ID3D11ShaderResourceView*> mTextureNormal;
	// ���_
	VERTEX_3D mVertex[FIELD_X][FIELD_X];


public:

	void Init();
	void Unint();
	void Update();
	void Render();

	// Getter
	float GetHeight(D3DXVECTOR3 pos);
};

