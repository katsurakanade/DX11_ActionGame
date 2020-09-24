#include "main.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"

void Animation::Init() {

	mState = "Idle";
	mNewState = "Idle";
	mFrame = 0;
}

void Animation::Uninit() {

}

void Animation::Update() {

	// Frame ����
	mFrame += mCoefficient * mAnimationSpeed * Time::GetDeltaTime();

	// Blend ����
	if (mState != mNewState) {
		mBlend += 3.0f * Time::GetDeltaTime();
	}

	if (mBlend >= 1.00f) {
		mState = mNewState;
		mBlend = 0.0f;
	}

	if (GetUsePanel()) {
		DataPanel();
	}

}

void Animation::FixedUpdate() {

	if (mFrame >= 1000000) {
		mFrame = 0;
	}

	if (mBlend < 0.0f) {
		mBlend = 0.0f;
	}

	if (mBlend >= 1.0f) {
		mBlend = 1.0f;
	}

}

void Animation::DataPanel() {

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"�A�j���[�V����")) {
		ImGui::Text("Frame : %f", mFrame);
		ImGui::Text(u8"�Đ����x : %f", (float)mCoefficient * (float)mAnimationSpeed);
		ImGui::Text(u8"Blend : %f", mBlend);
		ImGui::Text(u8"��� : %s", mState.c_str());
		ImGui::Text(u8"���(�V) : %s", mNewState.c_str());
		ImGui::TreePop();
		
	}
	ImGui::End();


}
