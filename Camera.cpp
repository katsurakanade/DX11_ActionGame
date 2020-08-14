#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

void Camera::Init() {

	Name = "Camera";

	Position = D3DXVECTOR3(0.0f, 110.0f, -5.0f);
	mTarget = D3DXVECTOR3(0.0f, 0.0f, 10.0f);

	mFollowPostionOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mFollowProjectionOffset = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}

void Camera::Uninit() {

}

void Camera::Update() {

	//mTarget = FollowTarget->Position + FollowProjectionOffset;
	//D3DXVECTOR3 foward = FollowTarget->GetForward();
	//Position = Target - foward * 5.0f + FollowPostionOffset;

	/*Position = D3DXVECTOR3(0.0f, 100.0f, -5.0f); + mFollowPostionOffset;
	mTarget = D3DXVECTOR3(0.0f, 0.0f, 15.0f); + mFollowProjectionOffset;*/


	/*if (Input::GetKeyPress('D')) {
		RotationAround(D3DXVECTOR3(0,0,0), 1.0f);
	}

	if (Input::GetKeyPress('A')) {
		RotationAround(D3DXVECTOR3(0, 0, 0), -1.0f);
	}*/

	/*ImGui::Begin(u8"カメラ");

	ImGui::Text("%f,%f,%f", Position.x, Position.y, Position.z);

	ImGui::Text("%f,%f,%f", mTarget.x, mTarget.y, mTarget.z);

	ImGui::SetWindowSize(ImVec2(500, 200));
	float fp[3] = { mFollowPostionOffset.x ,mFollowPostionOffset.y ,mFollowPostionOffset.z };
	ImGui::SliderFloat3(u8"座標", fp, -200.0f, 200.0f,"%.0f",2.0f);
	mFollowPostionOffset = D3DXVECTOR3(fp[0], fp[1], fp[2]);

	float fpr[3] = { mFollowProjectionOffset.x ,mFollowProjectionOffset.y ,mFollowProjectionOffset.z };
	ImGui::SliderFloat3(u8"視点", fpr, -200.0f, 200.0f, "%.0f", 2.0f);
	mFollowProjectionOffset = D3DXVECTOR3(fpr[0], fpr[1], fpr[2]);

	ImGui::End();*/

	
}

void Camera::Render() {

	//ビューマトリクス設定
	
	D3DXMatrixLookAtLH(&mViewMatrix, &Position, &mTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&mViewMatrix);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 10000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}