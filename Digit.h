/*
数字クラス
*/
#pragma once

#include "Resource.h"

class Digit : public Resource
{

private:

	// 画像
	std::vector <Sprite*> mNumberSprite;
	std::vector <Effect*> mNumberBillboard;
	// 桁
	int mFig;
	// 数値
	int mValue;
	
public:

	void Init();
	void Unint();
	void Update();
	void Render();

	// 数字画像生成
	void MakeSprite(int fig, D3DXVECTOR2 size);
	void MakeBillBoard(int fig, D3DXVECTOR2 size);

	// Setter
	void SetValue(int val) { mValue = val; };
};

