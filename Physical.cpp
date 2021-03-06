#include "main.h"
#include "Resource.h"
#include "Application.h"
#include "Physical.h"
#include "Time.h"

void Physical::Init() {

	mVelocity = D3DXVECTOR3(0, 0, 0);

}

void Physical::Uninit() {

}

void Physical::Update() {

	// 移動中
	if (IsMoving()) {

		if (mAcceleration > 0) {
			mAcceleration *= mSpeedDownCoefficient;
		}

		else if (mAcceleration < 0.00f) {
			mAcceleration = 0.00f;
		}

		if (mSpeed > 0) {
			mSpeed *= mSpeedDownCoefficient;
		}

		else if (mSpeed < 0.00f) {
			mSpeed = 0.00f;
		}
	}

	// 座標処理
	ProcessPostion();

	IsGround = false;


}

void Physical::FixedUpdate() {
	Component::FixedUpdate();
}


void Physical::AddForce(D3DXVECTOR3 force) {
	GetResource()->Position += force * 100.0f * Time::GetDeltaTime();
}

bool Physical::IsMoving() {

	if (mVelocity.x > 0 || mVelocity.x < 0) {
		return true;
	}

	if (mVelocity.y > 0 || mVelocity.y < 0) {
		return true;
	}

	if (mVelocity.z > 0 || mVelocity.z < 0) {
		return true;
	}

	return false;
}

void Physical::ProcessPostion() {

	// 移動速度
	GetResource()->Position += mVelocity * mSpeed * Time::GetDeltaTime();
	// ジャンプ速度
	GetResource()->Position += mForce * 3.0f * Time::GetDeltaTime();
}

void Physical::DataPanel() {

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"物理")) {
		ImGui::Text("Acc : %f ", mAcceleration);
		ImGui::Text("Speed : %f ", mSpeed);
		ImGui::Text("Vel : (%f,%f,%f)  ", mVelocity.x, mVelocity.y, mVelocity.z);
		ImGui::Text("Force : (%f,%f,%f)  ", mForce.x, mForce.y, mForce.z);
		ImGui::TreePop();
	}
	ImGui::End();
}

