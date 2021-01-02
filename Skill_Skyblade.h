#pragma once

#include "Resource.h"

class Skill_Skyblade : public Resource
{

private:

	Player* mpPlayer;
	Sprite* mMagicRing;
	ParticleSystem* mEffect;

	BoxCollider* mCollider;

	float mDamageTimer;
	float mKillTimer;

public:
	void Init();
	void Uninit();
	void Update();
	void Render();


};

