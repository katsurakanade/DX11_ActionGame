#pragma once

#include "Resource.h"

class Missile : public Resource
{

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// カーブブレンド
	float mCurveProgress = 0.0f;
	// 始点、中点、終点
	D3DXVECTOR3 p0, p1,p2;
	// エフェクト
	Effect* mpEffect;
	// ターゲットインデックス
	int mTargetIndex;

};

