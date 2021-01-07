#pragma once

#include "Resource.h"

class Skill_AttackAround : public Resource
{

private:

	Player* mpPlayer;
	BossBehavior* mpBossBehavior;
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

	void SetEnemy(BossBehavior* enemy) { mpBossBehavior = enemy; };
};

