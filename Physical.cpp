#include "main.h"
#include "Resource.h"
#include "Physical.h"

void Physical::Init() {

	mVelocity = D3DXVECTOR3(0, 0, 0);
	mSpeed = mSpeed_Start;
}

void Physical::Uninit() {

}

void Physical::Update(Resource* target) {

	target->Position += mVelocity* mSpeed;

	/*{
		ImGui::Begin(u8"•¨—");
		ImGui::Text(u8"Velocity %f %f %f",mVelocity.x, mVelocity.y, mVelocity.z);
		ImGui::Text(u8"Speed %f", mSpeed);
		ImGui::End();
	}*/

	if (IsMoving()) {
		if (mSpeed > 0) {
			mSpeed -= mSpeedDownCoefficient;
		}

		else if (mSpeed < 0.00f) {
			mSpeed = 0.00f;
		}
	}
	
}

void Physical::Start() {
	mSpeed = mSpeed_Start;
}

void Physical::AddForce(Resource* target,float force) {
	D3DXVECTOR3 vel;
	D3DXVec3Normalize(&vel, &mVelocity);
	target->Position += (vel * force);
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