#pragma once
#include "Resource.h"

class ParticleManager : public Resource
{

private:

	ParitcleSetting mSetting;
	ID3D11ShaderResourceView* mTexture = nullptr;

public:
	void Init();
	void Uninit();
	void Update();
};

