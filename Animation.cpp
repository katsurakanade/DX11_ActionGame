#include "main.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"

void Animation::Init() {

	mState = "Idle";
	mOldState = "Idle";
	mFrame = 0;

}

void Animation::Uninit() {

}

void Animation::Update() {

	if (mFrame >= 1000000) {
		mFrame = 0;
	}

	if (mState != mOldState) {
		mFrame = 0;
	}

	mFrame += mCoefficient * mAnimationSpeed * Time::GetDeltaTime();

	mOldState = mState;

	DataPanel();
}

void Animation::DataPanel() {

	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"アニメーション")) {
		ImGui::Text("Frame : %f", mFrame);
		ImGui::Text(u8"再生速度 : %f", (float)mCoefficient * (float)mAnimationSpeed);
		ImGui::Text(u8"状態 : %s", mState.c_str());
		ImGui::TreePop();
	}
	ImGui::End();
}