/*
ライトクラス
*/

#pragma once

#include "Resource.h"
#include "Renderer.h"

class Light : public Resource
{
	
private:

	// ソース
	LIGHT* mSource;

public:


	void Init();
	void Uninit();
	void Update();
	void Render();

	// Getter
	LIGHT* GetSource() { return mSource; };
};

