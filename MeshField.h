/*
メッシュフィールドクラス
*/

#pragma once

#include "Resource.h"


class MeshField : public Resource
{

private:

	// マップ
	static float HeightMap[FIELD_X][FIELD_X];
	// バッファ
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	// テクスチャ
	std::vector <ID3D11ShaderResourceView*> mTexture;
	// 頂点
	VERTEX_3D mVertex[FIELD_X][FIELD_X];
	// リセット
	//void ResetField();

public:

	void Init();
	void Unint();
	void Update();
	void Render();

	// Getter
	float GetHeight(D3DXVECTOR3 pos);
};

