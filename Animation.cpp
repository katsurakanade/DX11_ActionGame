#include "main.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"

void Animation::Init() {

	// データ初期化
	mState = "Idle";
	mNewState = "Idle";
	mFrame = 0;
}

void Animation::Uninit() {

}

void Animation::Update() {

	// フレーム処理
	mFrame += mCoefficient * mAnimationSpeed * Time::GetDeltaTime();

	// ブレンド処理
	if (mState != mNewState) {
		mBlend += 3.0f * Time::GetDeltaTime();
	}

	if (mBlend >= 1.00f) {
		mState = mNewState;
		mBlend = 0.0f;
	}

	// ForDebug
	if (GetUsePanel()) {
		DataPanel();
	}

}

void Animation::FixedUpdate() {

	// フレーム修正
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
	if (ImGui::TreeNode(u8"アニメーション")) {
		ImGui::Text("Frame : %f", mFrame);
		ImGui::Text(u8"再生速度 : %f", mCoefficient * mAnimationSpeed);
		ImGui::Text(u8"Blend : %f", mBlend);
		ImGui::Text(u8"状態 : %s", mState.c_str());
		ImGui::Text(u8"状態(新) : %s", mNewState.c_str());
		ImGui::TreePop();
		
	}
	ImGui::End();


}
