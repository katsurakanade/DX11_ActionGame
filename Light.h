#pragma once

#include "Resource.h"

class Light : public Resource
{
	
private:

	LIGHT* mSource;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	LIGHT* GetSource() { return mSource; };
};
