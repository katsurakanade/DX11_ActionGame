/*
�A�C�e���N���X
*/

#pragma once
#include "Resource.h"

class Item : public Resource
{

private:

	// ���f��
	AssimpModel* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// Setter
	void SetModel(AssimpModel* model) { mModel = model; };

};