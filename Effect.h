#pragma once
#include "Resource.h"

#define EFFECT_X_DEFAULT 4
#define EFFECT_Y_DEFAULT 4

class Effect : public Resource
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	D3DXVECTOR3 Size = D3DXVECTOR3(150.0f, 150.0f, 0.0f);
	int m_framecount;
	std::vector <std::vector <D3DXVECTOR2>> Frame;

	int width = EFFECT_X_DEFAULT;
	int height = EFFECT_Y_DEFAULT;
	float waitframe;

	D3DXVECTOR2 MakeFrame();

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetHW(int valx,int valy) { width = valx; height = valy; };

};

