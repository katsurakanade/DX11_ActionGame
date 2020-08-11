#include "main.h"
#include "Resource.h"
#include "Physical.h"

void Physical::Init() {

	mVelocity = D3DXVECTOR3(0, 0, 0);

}

void Physical::Uninit() {

}

void Physical::Update(Resource* target) {

	target->Position += mVelocity;

	{
		ImGui::Begin(u8"•¨—");
		ImGui::Text(u8"Velocity %f %f %f",mVelocity.x, mVelocity.y, mVelocity.z);
		ImGui::End();
	}
}


void Physical::AddForce(Resource* target,float force) {
	D3DXVECTOR3 vel;
	D3DXVec3Normalize(&vel, &mVelocity);
	target->Position += (vel * force);
}