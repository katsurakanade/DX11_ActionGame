/*
アイテムクラス
*/

#pragma once
#include "Resource.h"

class Item : public Resource
{

private:

	ModelManager* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter

};