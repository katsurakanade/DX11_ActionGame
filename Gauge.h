/*
ゲージクラス
*/
#pragma once

#include "Resource.h"

// 描画モード
enum class GaugeType {
	GAUGE_GUI,
	GAUGE_BILLBOARD,
};

class Gauge : public Resource
{

private:

	// 描画モード
	GaugeType mType;
	// ターゲット
	Resource* mpTarget;

	// 画像
	Sprite* mpBar_empty;
	Sprite* mpBar_fill;

	// 長さ（GUIモード）
	int mGuiLength;

public:

	// 偏移
	D3DXVECTOR3 mPositionOffest;
	// フィル
	float mFillAmount;

	void Init();
	void Uninit();
	void Update();
	void Render();
	// Setter
	void SetGUI(int length);
	void SetBillBoard(Resource* target);
};

