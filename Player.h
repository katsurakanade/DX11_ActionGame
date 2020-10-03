/*
プレイヤークラス
*/

#pragma once

#include "Resource.h"
#include "AssimpModel.h"

class Animation;

class Player : public Resource
{

private:

	// HP
	float mHpInit = 40000.0f;

	//bool mCanJump;
	//float mJumpVel = 0;
	//float mJumpTime = 0;

	// アニメーション速度
	float mAnimationSpeed = 3.0f;
	// アニメーション状態
	std::string mAnimationState = "Idle";
	// モデル
	AssimpModel* mModel;
	// ForDebug
	void SettingPanel();

	//void Jump(BYTE keykode);
	// 移動
	void Movement(BYTE keykodeF, BYTE keykodeB,BYTE keykodeR, BYTE keykodeL);
	// スキル
	void Skill(BYTE keykode_0, BYTE keykode_1, BYTE keykode_2, BYTE keykode_3);
	// ForDebug
	void CameraEditMode(BYTE keykode);
	// アニメーションポインタ
	Animation* mpAnination;

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

