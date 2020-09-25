#pragma once
#include "Resource.h"
class Item : public Resource
{

private:

	AssimpModel* mModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetModel(AssimpModel* model) { mModel = model; };

};

