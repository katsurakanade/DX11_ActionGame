#pragma once

#include "Component.h"

// �����N���X : ���\�[�X�N���X
class Physical : public Component
{

private:

	// ���x�����W��
	const float mSpeedDownCoefficient;
	// �ړ���
	bool IsMoving();
	// �n�ʂɂ���
	bool IsGround;
	// �d��
	const float mGravity;
	// ���W����
	void ProcessPostion();
	// �f�[�^�p�l��
	void DataPanel();

public:

	Physical() : mSpeedDownCoefficient(0.93f) ,mGravity(9.8f) , mAcceleration(0.0f) , mSpeed(0) , IsGround(true) {};

	// �����x
	float mAcceleration;
	// ���x
	float mSpeed;
	// ���x����
	D3DXVECTOR3 mVelocity;
	// �W�����v��
	D3DXVECTOR3 mForce;

	void Init();
	void Uninit();
	void Update();

	void AddForce(D3DXVECTOR3 force);

	void SpeedDown(float value) {
		mSpeed -= value;
	}

	bool GetIsGround() { return IsGround; };


};

