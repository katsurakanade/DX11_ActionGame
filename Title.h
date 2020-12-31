/*
タイトルシーンクラス
*/

#pragma once

#include "Scene.h"
#include "Sprite.h"

class Skybox;

class Title : public Scene
{
private:

	bool mStart = false;

	ParticleSystem* mParticle;
	Skybox* mSkybox;
	Sprite* mTitleIcon;
	Sprite* mButtonIcon;


	void CreateTitle();

public:

	void Init();
	void Update();
};

