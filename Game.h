#pragma once

#include "Scene.h"
#include "Skybox.h"
#include "Physical.h"
#include "Level.h"
#include "Player.h"
#include "GUI.h"
#include "Wall.h"

class Game : public Scene
{
private:

	bool mClear = false;

public:

	void Init();
	void Update();

};

