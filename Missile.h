#pragma once

#include "Resource.h"

class Missile : public Resource
{

public:

	void Init();
	void Uninit();
	void Update();
	void Render();

	// �J�[�u�u�����h
	float mCurveProgress = 0.0f;
	// �n�_�A���_�A�I�_
	D3DXVECTOR3 p0, p1,p2;
	// �G�t�F�N�g
	Effect* mpEffect;
	// �^�[�Q�b�g�C���f�b�N�X
	int mTargetIndex;

};

