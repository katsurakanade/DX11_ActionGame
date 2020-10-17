/*
”šƒNƒ‰ƒX
*/
#pragma once

#include "Resource.h"

class Digit : public Resource
{

private:

	// ‰æ‘œ
	std::vector <Sprite*> mNumberSprite;
	std::vector <Effect*> mNumberBillboard;
	// Œ…
	int mFig;
	// ”’l
	int mValue;
	
public:

	void Init();
	void Unint();
	void Update();
	void Render();

	// ”š‰æ‘œ¶¬
	void MakeSprite(int fig, D3DXVECTOR2 size);
	void MakeBillBoard(int fig, D3DXVECTOR2 size);

	// Setter
	void SetValue(int val) { mValue = val; };
};

