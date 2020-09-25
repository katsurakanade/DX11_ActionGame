#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

bool flag = false;

void Camera::Init() {

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

	if (mFollowTarget) {
		mTarget = mFollowTarget->Position + mFollowProjectionOffset;
		if (!flag) {
			Position = mTarget + mFollowPostionOffset + mControllerPosition;
		}		
	}

	ImGui::Begin(u8"�J����");

	ImGui::SliderFloat3(u8"���W", mFollowPostionOffset, -200.0f, 200.0f,"%.0f",2.0f);

	ImGui::SliderFloat3(u8"���_", mFollowProjectionOffset, -200.0f, 200.0f, "%.0f", 2.0f);

	ImGui::SliderFloat3(u8"�R���g���[��", mControllerPosition, -200.0f, 200.0f, "%.0f", 2.0f);

	ImGui::SliderFloat3(u8"���W", Position, -200.0f, 200.0f, "%.0f", 2.0f);

	ImGui::SliderFloat3(u8"���_", mTarget, -200.0f, 200.0f, "%.0f", 2.0f);


	ImGui::End();
	

	if (Input::GetKeyPress(DIK_C)) {

		/*float tx = mFollowTarget->Position.x;
		float ty = mFollowTarget->Position.z;
		float x0 = Position.x;
		float y0 = Position.z;

		mControllerPosition.x = tx + (x0 - tx) * cos(D3DXToRadian(5.0f * Time::GetDeltaTime())) - (y0 - ty) * sin(D3DXToRadian(5.0f * Time::GetDeltaTime()));*/
		//mControllerPosition.z = ty + (x0 - tx) * sin(D3DXToRadian(1.0f * Time::GetDeltaTime())) + (y0 - ty) * cos(D3DXToRadian(1.0f * Time::GetDeltaTime()));
	}
}

void Camera::Render() {

	//�r���[�}�g���N�X�ݒ�
	
	D3DXMatrixLookAtLH(&mViewMatrix, &Position, &mTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&mViewMatrix);

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);

	Renderer::SetCameraPosition(Position);

}