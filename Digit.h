/*
�����N���X
*/
#pragma once

#include "Resource.h"

class Digit : public Resource
{

private:

	// �摜
	std::vector <Sprite*> mNumberSprite;
	std::vector <Effect*> mNumberBillboard;
	// ��
	int mFig;
	// ���l
	int mValue;
	
public:

	void Init();
	void Unint();
	void Update();
	void Render();

	// �����摜����
	void MakeSprite(int fig, D3DXVECTOR2 size);
	void MakeBillBoard(int fig, D3DXVECTOR2 size);

	// Setter
	void SetValue(int val) { mValue = val; };
};

