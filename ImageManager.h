#pragma once

#include "Component.h"

class ImageManager : public Component
{

private:

	// �o�b�t�@
	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11Buffer* mColorBuffer = nullptr;
	// �e�N�X�`��
	ID3D11ShaderResourceView* mTexture = nullptr;
	// �T�C�X
	D3DXVECTOR3 mSize;


	// �A�j���[�V�����p
	bool mAnimation = false;
	int mFramecount;
	std::vector <std::vector <D3DXVECTOR2>> mFrame;
	int mWidth, mHeight;
	D3DXVECTOR2 MakeFrame();

	// �A�j���[�V�������x�����p
	float mWaitframe;
	float mAnimeSpeed;
	bool mLoop;

	// �r���{�[�h
	bool mBillBoard;
	//	FillAmount
	float mFillAmount;

public:

	ImageManager() : mSize(D3DXVECTOR3(64.0f,64.0f,0.0f)), mWidth(3) , mHeight(3) , mAnimeSpeed(1.0f), mFillAmount(1.0f) , mLoop(false), mBillBoard(false){};

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetTexture(ID3D11ShaderResourceView* texture) { mTexture = texture; };
	void Set2DPosition(D3DXVECTOR3 pos);
	void SetColor(D3DXVECTOR4 col);
	void Set2DSize(D3DXVECTOR3 value);
	void SetAnimationSprite(bool val) { mAnimation = val; };
	void SetBillBoard(bool val) { mBillBoard = val; };
	void SetLoop(bool val) { mLoop = val; };
	void SetFrame(int frame) { mFramecount = frame; };
	void SetHW(int valx, int valy) { mWidth = valx; mHeight = valy; };
	void SetAnimationSpeed(float val) { mAnimeSpeed = val; };
	void SetFillAmount(float val) { mFillAmount = val; };

	// Getter
	D3DXVECTOR3 GetSize() { return mSize; };
	bool GetIsBillBoard() { return mBillBoard; };
};

