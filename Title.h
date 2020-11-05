/*
タイトルシーンクラス
*/

#pragma once

#include "Scene.h"
#include "Sprite.h"

class Title : public Scene
{
private:

	bool mStart = false;
	
public:

	void Init();
	void Update();
};

