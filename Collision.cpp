#include "main.h"
#include "Renderer.h"
#include "Collision.h"

void BoxCollider::Init() {

	Name = "Field";

	VERTEX_3D vertex[8];

	vertex[0].Position = D3DXVECTOR3(Position.x - (Size.x / 2), Position.y + (Size.y / 2), Position.z + (Size.z / 2));
	vertex[1].Position = D3DXVECTOR3(Position.x + (Size.x / 2), Position.y + (Size.y / 2),Position.z + (Size.z / 2));
	vertex[2].Position = D3DXVECTOR3(Position.x - (Size.x / 2), Position.y + (Size.y / 2), Position.z - (Size.z / 2));
	vertex[3].Position = D3DXVECTOR3(Position.x + (Size.x / 2), Position.y + (Size.y / 2), Position.z - (Size.z / 2));
	vertex[4].Position = D3DXVECTOR3(Position.x - (Size.x / 2), Position.y - (Size.y / 2), Position.z + (Size.z / 2));
	vertex[5].Position = D3DXVECTOR3(Position.x + (Size.x / 2), Position.y - (Size.y / 2),Position.z + (Size.z / 2));
	vertex[6].Position = D3DXVECTOR3(Position.x - (Size.x / 2),Position.y - (Size.y / 2), Position.z - (Size.z / 2));
	vertex[7].Position = D3DXVECTOR3(Position.x + (Size.x / 2), Position.y - (Size.y / 2), Position.z - (Size.z / 2));

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

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

}

void BoxCollider::Uninit() {

	m_VertexBuffer->Release();
}

void BoxCollider::Update(D3DXVECTOR3 pos ,D3DXVECTOR3 rot ,D3DXVECTOR3 scl){

	Position = pos;
	Rotation = rot;
	Scale = scl;
}

void BoxCollider::Render() {

	if (Renderer::GizmosMode){
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
		D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);

		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Renderer::GetDeviceContext()->Draw(8, 0);
	}
}

bool BoxCollider::Collision_Box_Stay(BoxCollider* target) {

	D3DXVECTOR3 selfmin = Position + D3DXVECTOR3(-(Size.x * Scale.x) / 2, (Size.y * Scale.y) / 2, -(Size.z * Scale.z) / 2);
	D3DXVECTOR3 selfmax =Position + D3DXVECTOR3((Size.x * Scale.x) / 2, -(Size.y * Scale.y) / 2, (Size.z * Scale.z) / 2);
	D3DXVECTOR3 targetmin = target->Position + D3DXVECTOR3(-(target->Size.x * target->Scale.x) / 2, (target->Size.y * target->Scale.y) / 2, -(target->Size.z * target->Scale.z) / 2);
	D3DXVECTOR3 targetmax = target->Position + D3DXVECTOR3((target->Size.x * target->Scale.x) / 2, -(target->Size.y * target->Scale.y) / 2, (target->Size.z * target->Scale.z) / 2);

	if (selfmax.z > targetmin.z&& selfmin.z < targetmax.z) {
		if (selfmax.x > targetmin.x&& selfmin.x < targetmax.x) {
			if (selfmax.y < targetmin.y && selfmin.y > targetmax.y) {
				return true;
			}
		}
	}

	return false;

}