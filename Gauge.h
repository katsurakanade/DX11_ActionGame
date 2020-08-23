#pragma once

#include "Resource.h"
#include "Effect.h"

enum GaugeType {
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
	float mFillAmount = 1.0f;

	void Init();
	void Unint();
	void Update();
	void Render();

	void SetGUI(int length);
	void SetBillBoard(Resource* target);
};

