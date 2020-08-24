#pragma once

#include "Resource.h"
#include "AssimpModel.h"
#include "Arrow.h"
#include "Collision.h"

class Ball : public Resource
{
private:

	static int ID;

	AssimpModel* mModel;
	Arrow* mArrow;

	void ReflectWall();
	void ReflectBall();

	int TexutreIndex = 0;

public:

	bool Change = false;

	void Init();
	void Uninit();
	void Update();
	void Render();

	void InitArrowPosition() {
		mArrow->Position = Position + D3DXVECTOR3(3, 0, 0);
	}
	void SetArrow(bool active) { 
		mArrow->SetActive(active);
	};
	void SetModelTexture(int val) {
		TexutreIndex = val;
	}

};

