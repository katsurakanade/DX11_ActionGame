#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

void Camera::Init() {

	Name = "Camera";

	Position = D3DXVECTOR3(0.0f, 40.0f, -55.0f);
	mTarget = D3DXVECTOR3(0.0f, 20.0f, 10.0f);

	mFollowPostionOffset = D3DXVECTOR3(0.0f, 20.0f, -60.0f);
	mFollowProjectionOffset = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}

void Camera::Uninit() {

}

void Camera::Update() {

	//mTarget = FollowTarget->Position + FollowProjectionOffset;
	//D3DXVECTOR3 foward = FollowTarget->GetForward();
	//Position = Target - foward * 5.0f + FollowPostionOffset;

	if (Input::GetKeyPress('D')) {
		Position.x += 0.3f;
		Position.z += 0.3f;
	}

	if (Input::GetKeyPress('A')) {
		Position.x -= 0.3f;
		Position.z -= 0.3f;
	}

	ImGui::Begin(u8"カメラ");

	ImGui::Text("%f,%f,%f", Position.x, Position.y, Position.z);

	ImGui::Text("%f,%f,%f", mTarget.x, mTarget.y, mTarget.z);

	/*ImGui::SetWindowSize(ImVec2(500, 200));
	float fp[3] = { FollowPostionOffset.x ,FollowPostionOffset.y ,FollowPostionOffset.z };
	ImGui::SliderFloat3(u8"座標", fp, -200.0f, 200.0f,"%.0f",2.0f);
	FollowPostionOffset = D3DXVECTOR3(fp[0], fp[1], fp[2]);

	float fpr[3] = { FollowProjectionOffset.x ,FollowProjectionOffset.y ,FollowProjectionOffset.z };
	ImGui::SliderFloat3(u8"視点", fpr, -200.0f, 200.0f, "%.0f", 2.0f);
	FollowProjectionOffset = D3DXVECTOR3(fpr[0], fpr[1], fpr[2]);*/

	ImGui::End();

	
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