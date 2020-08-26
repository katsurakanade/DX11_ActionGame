#pragma once

#include "Resource.h"

class Digit : public Resource
{

private:


	std::vector <Sprite*> mNumberSprite;
	int mFig;
	int mValue;
	
public:

	void Init();
	void Unint();
	void Update();
	void Render();

	void MakeSprite(int fig, D3DXVECTOR2 size);

	void SetValue(int val) { mValue = val; };
};

