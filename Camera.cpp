#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

int Camera::ID = -1;

void Camera::Init() {

	Name = "Camera_" + std::to_string(Camera::ID);

	Position = D3DXVECTOR3(0.0f, 10.0f, -40.0f);
	mTarget = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	mFollowPostionOffset = D3DXVECTOR3(0.0f, 3.0f, 10.0f);
	mFollowProjectionOffset = D3DXVECTOR3(0.0f, 15.0f,14.0f);

	mControllerPosition = D3DXVECTOR3(0.0f, -3.0f, 5.0f);
}

void Camera::Uninit() {

}

void Camera::Update() {

	// 追跡
	if (mFollowTarget) {
		mTarget = mFollowTarget->Position + mFollowProjectionOffset + mControllerPosition;
		Position = mTarget + mFollowPostionOffset + mControllerPosition;
	}

	if (mLookTarget) {
		mTarget = mLookTarget->Position;
	}

	// カメラ操作
	if (Input::GetKeyPress(DIK_J)) {
		mControllerPosition += D3DXVECTOR3(-5.0f, 0, 0) * Time::GetDeltaTime();
	}
	if (Input::GetKeyPress(DIK_K)) {
		mControllerPosition += D3DXVECTOR3(5.0f, 0, 0) * Time::GetDeltaTime();
	}
	if (Input::GetKeyPress(DIK_U)) {
		mControllerPosition += D3DXVECTOR3(0, 5.0f, 0) * Time::GetDeltaTime();
	}
	if (Input::GetKeyPress(DIK_I)) {
		mControllerPosition += D3DXVECTOR3(0, -5.0f, 0) * Time::GetDeltaTime();
	}

	ImGui::Begin(u8"システム");

	if (ImGui::TreeNode(u8"カメラ")) {
		if (mFollowTarget) {
			ImGui::SliderFloat3(u8"座標偏移", mFollowPostionOffset, -200.0f, 200.0f, "%.0f", 2.0f);
			ImGui::SliderFloat3(u8"視点偏移", mFollowProjectionOffset, -200.0f, 200.0f, "%.0f", 2.0f);
			ImGui::SliderFloat3(u8"コントロール", mControllerPosition, -200.0f, 200.0f, "%.0f", 2.0f);
		}

		else {
			ImGui::SliderFloat3(u8"座標", Position, -200.0f, 200.0f, "%.0f", 2.0f);
			ImGui::SliderFloat3(u8"視点", mTarget, -200.0f, 200.0f, "%.0f", 2.0f);
		}
		ImGui::TreePop();
	}

	ImGui::End();
	
}

void Camera::Render() {

	D3DXMatrixLookAtLH(&mViewMatrix, &Position, &mTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&mViewMatrix);


	D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&mProjectionMatrix);

	Renderer::SetCameraPosition(Position);

}

bool Camera::CheckInView(D3DXVECTOR3 tpos) {

	D3DXMATRIX invvp;
	vp = mViewMatrix * mProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	for (int i = 0; i < 4; i++) {
		D3DXVec3TransformCoord(&wpos[i], &vpos[i], &invvp);
	}

	D3DXVECTOR3 v, nor, v1, v2;
	v = tpos - Position;
	v1 = wpos[0] - Position;
	v2 = wpos[2] - Position;
	D3DXVec3Cross(&nor, &v1, &v2);

	if (D3DXVec3Dot(&nor, &v) < 0.0f)
		return false;

	v1 = wpos[1] - Position;
	v2 = wpos[3] - Position;
	D3DXVec3Cross(&nor, &v1, &v2);

	if (D3DXVec3Dot(&nor, &v) > 0.0f)
		return false;

	v1 = wpos[0] - Position;
	v2 = wpos[1] - Position;
	D3DXVec3Cross(&nor, &v1, &v2);

	if (D3DXVec3Dot(&nor, &v) > 0.0f)
		return false;

	v1 = wpos[2] - Position;
	v2 = wpos[3] - Position;
	D3DXVec3Cross(&nor, &v1, &v2);

	if (D3DXVec3Dot(&nor, &v) < 0.0f)
		return false;

	return true;
}