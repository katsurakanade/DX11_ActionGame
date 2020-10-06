#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

bool flag = false;

void Camera::Init() {

	// ������
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

	// �ǐ�
	if (mFollowTarget) {
		mTarget = mFollowTarget->Position + mFollowProjectionOffset;
		if (!flag) {
			Position = mTarget + mFollowPostionOffset + mControllerPosition;
		}		
	}

	ImGui::Begin(u8"�J����");

	if (mFollowTarget) {
		ImGui::SliderFloat3(u8"���W�Έ�", mFollowPostionOffset, -200.0f, 200.0f, "%.0f", 2.0f);
		ImGui::SliderFloat3(u8"���_�Έ�", mFollowProjectionOffset, -200.0f, 200.0f, "%.0f", 2.0f);
		ImGui::SliderFloat3(u8"�R���g���[��", mControllerPosition, -200.0f, 200.0f, "%.0f", 2.0f);
	}

	else {
		ImGui::SliderFloat3(u8"���W", Position, -200.0f, 200.0f, "%.0f", 2.0f);
		ImGui::SliderFloat3(u8"���_", mTarget, -200.0f, 200.0f, "%.0f", 2.0f);
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