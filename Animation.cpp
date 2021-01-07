#include "main.h"
#include "Renderer.h"
#include "Time.h"
#include "Resource.h"
#include "Animation.h"
#include "Physical.h"

void Animation::Init() {

	// �f�[�^������
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

	// �t���[������
	if (!mPauseFrame)
		mFrame += 60.0f * mCoefficient * Time::GetDeltaTime();
	else
		return;

	// �u�����h����
	if (mState != mNewState) {
		mBlend += 7.0f * Time::GetDeltaTime();
	}

	// �J��
	if (mBlend >= 1.00f) {
		mState = mNewState;
		mBlend = 0.0f;
	}

	// ���A�j���[�V�����p
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

	Component::FixedUpdate();

	// �t���[���C��
	if (mFrame >= 1000000) 
		mFrame = 0;
	// �u�����h�C��
	if (mBlend < 0.0f) 
		mBlend = 0.0f;
	if (mBlend >= 1.0f) 
		mBlend = 1.0f;

}

void Animation::DataPanel() {

	// ImGui
	ImGui::Begin(GetResource()->Name.c_str());
	if (ImGui::TreeNode(u8"�A�j���[�V����")) {
		ImGui::Text("Frame : %f", mFrame);
		ImGui::Text(u8"�Đ����x : %f", mCoefficient);
		ImGui::Text(u8"Blend : %f", mBlend);
		ImGui::Text(u8"WaitTime : %f", mWaitTime);
		ImGui::Text(u8"OneTimeFlag : %d", mOneTimeFlag);
		ImGui::Text(u8"��� : %s", mState.c_str());
		ImGui::Text(u8"���(�V) : %s", mNewState.c_str());
		ImGui::Text(u8"���(��) : %s", mOldState.c_str());
		ImGui::TreePop();
	}
	ImGui::End();

}

void Animation::SetNewStateOneTime(std::string str,float timetowait) {

	if (mWaitTime == 0.0f && mNewState == mState) {
		mFrame = 0;
		mOldState = mState;
		mNewState = str;
		mOneTimeFlag = true;
		mTimeToWait = timetowait;
	}

}