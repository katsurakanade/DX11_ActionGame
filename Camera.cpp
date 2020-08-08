#include "main.h"
#include "Renderer.h"
#include "input.h"
#include "Application.h"
#include "Scene.h"
#include "Camera.h"

void Camera::Init() {

	Name = "Camera";

	Position = D3DXVECTOR3(0.0f, 2.0f, -100.0f);
	Target = D3DXVECTOR3(0.0f, 0.0f, 5.0f);

	FollowPostionOffset = D3DXVECTOR3(0.0f, 20.0f, -60.0f);
	FollowProjectionOffset = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}

void Camera::Uninit() {

}

void Camera::Update() {

	Target = FollowTarget->Position + FollowProjectionOffset;
	D3DXVECTOR3 foward = FollowTarget->GetForward();
	Position = Target - foward * 5.0f + FollowPostionOffset;

	ImGui::Begin(u8"カメラ");
	ImGui::SetWindowSize(ImVec2(500, 200));
	float fp[3] = { FollowPostionOffset.x ,FollowPostionOffset.y ,FollowPostionOffset.z };
	ImGui::SliderFloat3(u8"座標", fp, -200.0f, 200.0f,"%.0f",2.0f);
	FollowPostionOffset = D3DXVECTOR3(fp[0], fp[1], fp[2]);

	float fpr[3] = { FollowProjectionOffset.x ,FollowProjectionOffset.y ,FollowProjectionOffset.z };
	ImGui::SliderFloat3(u8"視点", fpr, -200.0f, 200.0f, "%.0f", 2.0f);
	FollowProjectionOffset = D3DXVECTOR3(fpr[0], fpr[1], fpr[2]);

	ImGui::End();

	
}

void Camera::Render() {

	//ビューマトリクス設定
	
	D3DXMatrixLookAtLH(&viewMatrix, &Position, &Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&viewMatrix);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 10000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}