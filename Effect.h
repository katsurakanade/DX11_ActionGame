/*
�G�t�F�N�g�N���X
*/

#pragma once
#include "Resource.h"

// �f�t�H���g�t���[��
#define EFFECT_X_DEFAULT 4
#define EFFECT_Y_DEFAULT 4

class Effect : public Resource
{
private:

	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer = NULL;
	ID3D11Buffer* mColorBuffer = NULL;
	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = NULL;
	// �T�C�Y
	D3DXVECTOR3 mSize = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	// �t���[����
	int mFramecount;
	// �t���[��
	std::vector <std::vector <D3DXVECTOR2>> mFrame;

	// ���c
	int mWidth = EFFECT_X_DEFAULT;
	int mHeight = EFFECT_Y_DEFAULT;

	// ���x�����p
	float mWaitframe;
	float mAnimeSpeed = 1.0f;
	bool mLoop = false;

	// �t���[������
	D3DXVECTOR2 MakeFrame();

	// �t�B��
	float mFillAmount = 1.0f;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetHW(int valx,int valy) { mWidth = valx; mHeight = valy; };
	void SetTexture(ID3D11ShaderResourceView* value) { mTexture = value; };
	void SetLoop(bool val) { mLoop = val; };
	void SetFillAmount(float val) { mFillAmount = val; };
	void SetAnimeSpeed(float val) { mAnimeSpeed = val; };
};

