#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

void Camera::Init() {

	// 初期化
	Name = "Camera";

	Position = D3DXVECTOR3(0.0f, 10.0f, -40.0f);
	mTarget = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	mFollowPostionOffset = D3DXVECTOR3(0.0f, 3.0f, 10.0f);
	mFollowProjectionOffset = D3DXVECTOR3(0.0f, 15.0f,14.0f);

	mControllerPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	ImGui::Begin(u8"カメラ");

	if (mFollowTarget) {
		ImGui::SliderFloat3(u8"座標偏移", mFollowPostionOffset, -200.0f, 200.0f, "%.0f", 2.0f);
		ImGui::SliderFloat3(u8"視点偏移", mFollowProjectionOffset, -200.0f, 200.0f, "%.0f", 2.0f);
		ImGui::SliderFloat3(u8"コントロール", mControllerPosition, -200.0f, 200.0f, "%.0f", 2.0f);
	}

	else {
		ImGui::SliderFloat3(u8"座標", Position, -200.0f, 200.0f, "%.0f", 2.0f);
		ImGui::SliderFloat3(u8"視点", mTarget, -200.0f, 200.0f, "%.0f", 2.0f);
	}

	ImGui::End();
	
}

void Camera::Render() {

	D3DXMatrixLookAtLH(&mViewMatrix, &Position, &mTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&mViewMatrix);

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);

	Renderer::SetCameraPosition(Position);

}