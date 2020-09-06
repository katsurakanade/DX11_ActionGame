#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

void Camera::Init() {

	Name = "Camera";

	Position = D3DXVECTOR3(0.0f, 10.0f, -40.0f);
	mTarget = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	mFollowPostionOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mFollowProjectionOffset = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}

void Camera::Uninit() {

}

void Camera::Update() {

	if (mFollowTarget) {
		mTarget.x = mFollowTarget->Position.x + mFollowProjectionOffset.x;
		//D3DXVECTOR3 foward = mFollowTarget->GetForward();
		//Position = mTarget - foward * 5.0f + mFollowPostionOffset;
	}

	ImGui::Begin(u8"�J����");

	float fp[3] = { Position.x ,Position.y ,Position.z };
	ImGui::SliderFloat3(u8"���W", fp, -200.0f, 200.0f,"%.0f",2.0f);
	Position = D3DXVECTOR3(fp[0], fp[1], fp[2]);

	float fpr[3] = { mTarget.x ,mTarget.y ,mTarget.z };
	ImGui::SliderFloat3(u8"���_", fpr, -200.0f, 200.0f, "%.0f", 2.0f);
	mTarget = D3DXVECTOR3(fpr[0], fpr[1], fpr[2]);

	ImGui::End();

	
}

void Camera::Render() {

	//�r���[�}�g���N�X�ݒ�
	
	D3DXMatrixLookAtLH(&mViewMatrix, &Position, &mTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&mViewMatrix);

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 10000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}