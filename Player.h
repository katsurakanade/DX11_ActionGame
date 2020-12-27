/*
プレイヤークラス
*/

#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;
class BoxCollider;
class PlayerBehavior;

class Player : public Resource
{

private:

	// HP
	float mHpInit = 40000.0f;
	// ForDebug
	void SettingPanel();
	// コンポーネント
	Animation* mpAnination;
	ModelManager* mpModel;
	Physical* mpPhysical;
	BoxCollider* mpCollider;
	PlayerBehavior* mpPlayerBehavior;
	// メインカメラポインタ
	Camera* mpCamera;

public:

	// HP
	float mHp;

	void Init();
	void Unint();
	void Update();
	void Render();

	// Getter
	float GetHpInit(){ return mHpInit; };
};

