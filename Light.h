/*
���C�g�N���X
*/

#pragma once

#include "Resource.h"
#include "Renderer.h"

class Light : public Resource
{
	
private:

	// �\�[�X
	LIGHT* mSource;

public:


	void Init();
	void Uninit();
	void Update();
	void Render();

	// Getter
	LIGHT* GetSource() { return mSource; };
};

