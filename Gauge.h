#pragma once

#include "Resource.h"
#include "Effect.h"

enum class GaugeType {
	GAUGE_GUI,
	GAUGE_BILLBOARD,
};

class Gauge : public Resource
{

private:

	GaugeType mType;
	Resource* mpTarget;

	Effect* mpBar_empty;
	Effect* mpBar_fill;

	int mGuiLength;

public:

	D3DXVECTOR3 mPositionOffest;
	float mFillAmount;

	void Init();
	void Uninit();
	void Update();
	void Render();

	void SetGUI(int length);
	void SetBillBoard(Resource* target);
};

