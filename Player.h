/*
プレイヤークラス
*/

#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;
class ModelManager;

class Player : public Resource
{

private:

	// HP
	float mHpInit = 40000.0f;
	// キャラタイプ
	int mCharacterType;
	// ForDebug
	void SettingPanel();
	// 移動
	void Movement(BYTE keykodeF, BYTE keykodeB,BYTE keykodeR, BYTE keykodeL);
	// スキル
	void Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3);
	// アニメーションポインタ
	Animation* mpAnination;
	ModelManager* mpModel;
	// メインカメラポインタ
	Camera* mpCamera;
	// ロックしている敵インデックス
	unsigned int mLockIndex;

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

