#pragma once

#include "Resource.h"
#include "model.h"

class Torus : public Resource
{

private:

	AssimpModel* mModel;
	CModel* mCmodel;

public:

	bool Simple;

	void Init();
	void Uninit();
	void Update();
	void Render();
};

