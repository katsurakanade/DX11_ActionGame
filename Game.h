/*
ゲームシーンクラス
*/

#pragma once

#include "Scene.h"
#include "Skybox.h"
#include "Physical.h"
#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "Digit.h"

class Game : public Scene
{

private:

public:

	void Init();
	void Update();

};

