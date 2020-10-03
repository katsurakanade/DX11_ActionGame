/*
�Q�[�W�N���X
*/
#pragma once

#include "Resource.h"
#include "Effect.h"

// �`�惂�[�h
enum class GaugeType {
	GAUGE_GUI,
	GAUGE_BILLBOARD,
};

class Gauge : public Resource
{

private:

	// �`�惂�[�h
	GaugeType mType;
	// �^�[�Q�b�g
	Resource* mpTarget;

	// �摜
	Effect* mpBar_empty;
	Effect* mpBar_fill;

	// �����iGUI���[�h�j
	int mGuiLength;

public:

	// �Έ�
	D3DXVECTOR3 mPositionOffest;
	// �t�B��
	float mFillAmount;

	void Init();
	void Uninit();
	void Update();
	void Render();
	// Setter
	void SetGUI(int length);
	void SetBillBoard(Resource* target);
};

