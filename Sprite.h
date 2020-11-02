/*
スプライトクラス
*/
#pragma once

#include "Resource.h"

class ImageManager;

class Sprite : public Resource {

private:

	ImageManager* mImage;

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	ImageManager* GetImage() { return mImage; };
};

