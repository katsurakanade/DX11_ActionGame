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
	mOldState = "Idle";
	mOneTimeFlag = false;
	mFrame = 0;
	mWaitTime = 0.0f;

}

void Animation::Uninit() {

}

void Animation::Update() {

	// フレーム処理
	mFrame += 60.0f * Time::GetDeltaTime();

	// ブレンド処理
	if (mState != mNewState) {
		mBlend += 5.0f * Time::GetDeltaTime();
	}

	// 遷移
	if (mBlend >= 1.00f) {
		mState = mNewState;
		mBlend = 0.0f;
	}

	// ForDebug
	if (GetUsePanel()) {
		DataPanel();
	}

	if (mOneTimeFlag) {
		mWaitTime += 1.0f * Time::GetDeltaTime();
	}

	if (mOneTimeFlag && mWaitTime >= mTimeToWait) {
		mWaitTime = 0.0f;
		mNewState = mOldState;
		mOneTimeFlag = false;
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
		ImGui::Text(u8"WaitTime : %f", mWaitTime);
		ImGui::Text(u8"OneTimeFlag : %d", mOneTimeFlag);
		ImGui::Text(u8"状態 : %s", mState.c_str());
		ImGui::Text(u8"状態(新) : %s", mNewState.c_str());
		ImGui::Text(u8"状態(旧) : %s", mOldState.c_str());
		ImGui::TreePop();
	}
	ImGui::End();

}

void Animation::SetNewStateOneTime(std::string str,float timetowait) {

	if (mWaitTime != 0.0f) {
		return;
	}

	mFrame = 0;
	mOldState = mState;
	mNewState = str;
	mOneTimeFlag = true;
	mTimeToWait = timetowait;
}