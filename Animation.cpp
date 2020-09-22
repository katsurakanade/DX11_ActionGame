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
	mExitFlag = false;

}

void Animation::Uninit() {

}

void Animation::Update() {

	if (mFrame >= 1000000) {
		mFrame = 0;
	}

	mFrame += mCoefficient * mAnimationSpeed * Time::GetDeltaTime();

	if (mState != mNewState) {
		mBlend += 3.0f * Time::GetDeltaTime();
	}

	if (mBlend >= 1.0f) {
		mState = mNewState;
		mBlend = 0.0f;
	}

	if (GetUsePanel()) {
		DataPanel();
	}
}

void Animation::DataPanel() {

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"アニメーション")) {
		ImGui::Text("Frame : %f", mFrame);
		ImGui::Text(u8"再生速度 : %f", (float)mCoefficient * (float)mAnimationSpeed);
		ImGui::Text(u8"状態 : %s", mState.c_str());
		ImGui::Text(u8"状態(旧) : %s", mNewState.c_str());
		ImGui::TreePop();
	}
	ImGui::End();
}