/*
行為クラス
*/
#pragma once
#include "Component.h"

class Physical;
class Animation;
class Player;

// ステート
enum class BEHAVIOR_STATE{
	Idle, // 待機
	Chase, // 追跡
	Attack, // 攻撃
};

class Behavior : public Component
{

private:

	// ステート
	BEHAVIOR_STATE mState;
	// コンポーネント
	Physical* mpPhysical;
	Animation* mpAnimation;
	// プレイヤーポインタ
	Player* mpPlayer;
	// 移動
	void Movement(int arrow);
	// 場所に移動
	void MoveTo(D3DXVECTOR3 target_position);

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

};

