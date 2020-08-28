#include "main.h"
#include "Renderer.h"
#include "Resource.h"
#include "Collision.h"

void BoxCollider::Init() {

	Name = "Field";

	VERTEX_3D vertex[8];

	vertex[0].Position = D3DXVECTOR3(Position.x - (mSize.x / 2), Position.y + (mSize.y / 2), Position.z + (mSize.z / 2));
	vertex[1].Position = D3DXVECTOR3(Position.x + (mSize.x / 2), Position.y + (mSize.y / 2),Position.z + (mSize.z / 2));
	vertex[2].Position = D3DXVECTOR3(Position.x - (mSize.x / 2), Position.y + (mSize.y / 2), Position.z - (mSize.z / 2));
	vertex[3].Position = D3DXVECTOR3(Position.x + (mSize.x / 2), Position.y + (mSize.y / 2), Position.z - (mSize.z / 2));
	vertex[4].Position = D3DXVECTOR3(Position.x - (mSize.x / 2), Position.y - (mSize.y / 2), Position.z + (mSize.z / 2));
	vertex[5].Position = D3DXVECTOR3(Position.x + (mSize.x / 2), Position.y - (mSize.y / 2),Position.z + (mSize.z / 2));
	vertex[6].Position = D3DXVECTOR3(Position.x - (mSize.x / 2),	Position.y - (mSize.y / 2), Position.z - (mSize.z / 2));
	vertex[7].Position = D3DXVECTOR3(Position.x + (mSize.x / 2), Position.y - (mSize.y / 2), Position.z - (mSize.z / 2));

	for (int i = 0; i < 8; i++) {
		vertex[i].Normal = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(float) * 4;
	cbd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;

	Renderer::GetDevice()->CreateBuffer(&cbd, &sd, &mColorBuffer);
}

void BoxCollider::Uninit() {

	mVertexBuffer->Release();
}

void BoxCollider::Update(Resource* target){

	Position = target->Position + (mPositionOffest);
	//Rotation = target->Rotation;
	Scale = target->Scale + (mScaleOffest);
}

void BoxCollider::Render() {

	if (Renderer::mGizmosMode){

		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
		D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);

		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(mColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		float* col = (float*)msr.pData;
		col[0] = 0;
		col[1] = 1;
		col[2] = 0;
		col[3] = 1;
		Renderer::GetDeviceContext()->Unmap(mColorBuffer, 0);

		Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &mColorBuffer);

		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Renderer::GetDeviceContext()->Draw(8, 0);

	}

}

bool BoxCollider::Collision_Box_Stay(BoxCollider* target) {

	D3DXVECTOR3 selfmin = Position + D3DXVECTOR3(-(mSize.x * Scale.x) / 2, (mSize.y * Scale.y) / 2, -(mSize.z * Scale.z) / 2);
	D3DXVECTOR3 selfmax =Position + D3DXVECTOR3((mSize.x * Scale.x) / 2, -(mSize.y * Scale.y) / 2, (mSize.z * Scale.z) / 2);
	D3DXVECTOR3 targetmin = target->Position + D3DXVECTOR3(-(target->mSize.x * target->Scale.x) / 2, (target->mSize.y * target->Scale.y) / 2, -(target->mSize.z * target->Scale.z) / 2);
	D3DXVECTOR3 targetmax = target->Position + D3DXVECTOR3((target->mSize.x * target->Scale.x) / 2, -(target->mSize.y * target->Scale.y) / 2, (target->mSize.z * target->Scale.z) / 2);

	if (selfmax.z > targetmin.z&& selfmin.z < targetmax.z) {
		if (selfmax.x > targetmin.x&& selfmin.x < targetmax.x) {
			if (selfmax.y < targetmin.y && selfmin.y > targetmax.y) {
				return true;
			}
		}
	}

	return false;

}

bool BoxCollider::Collision_Box_Enter(BoxCollider* target) {

	mStay = Collision_Box_Stay(target);

	// Enter
	if (mStay && !mTriggerFlag) {
		DebugOutputString("Enter");
		mTriggerFlag = true;
		return true;
	}

	else if (!mStay && mTriggerFlag) {
		DebugOutputString("Exit");
		mTriggerFlag = false;
		return false;
	}

	return false;
}





