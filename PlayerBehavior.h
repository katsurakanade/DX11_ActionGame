/*
プレイヤー行為クラス
*/
#pragma once
#include "Component.h"

class BoxCollider;
class Physical;
class Animation;
class ModelManager;

class PlayerBehavior : public Component
{

private:

	// コンポーネント
	Physical* mpPhysical;
	Animation* mpAnimation;
	BoxCollider* mpCollider;
	ModelManager* mpModelManager;

	// メインカメラポインタ
	Camera* mpCamera;

	// キャラタイプ
	int mCharacterType;
	// ロックしている敵インデックス
	unsigned int mLockIndex;

	// 移動
	void Movement(BYTE keycodeF, BYTE keycodeB, BYTE keycodeR, BYTE keycodeL);
	// スキル
	void Skill(BYTE keycode_0, BYTE keycode_1, BYTE keycode_2, BYTE keycode_3);
	// キャラクター切替
	void SwitchCharacter(BYTE keycode_prev, BYTE keycode_next);
	// 目標ロック
	void LockTarget(BYTE keycode_lock);


public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();
};

