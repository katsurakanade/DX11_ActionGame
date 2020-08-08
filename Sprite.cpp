#include "main.h"
#include "Renderer.h"
#include "model.h"
#include "Sprite.h"
#include "Scene.h"
#include "input.h"

void Sprite::Init() {

	Name = "Sprite";

	VERTEX_3D vertex[4];

	Position = D3DXVECTOR3(750, 900, 0);

	vertex[0].Position = D3DXVECTOR3(Position.x, Position.y, 0.0f);
	vertex[1].Position = D3DXVECTOR3(Position.x + Size.x, Position.y, 0.0f);
	vertex[2].Position = D3DXVECTOR3(Position.x, Position.y + Size.y, 0.0f);
	vertex[3].Position = D3DXVECTOR3(Position.x + Size.x, Position.y + Size.y, 0.0f);

	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

}

void Sprite::Uninit() {

	VertexBuffer->Release();
	
}

void Sprite::Update() {

	if (Input::GetKeyTrigger('B')) {
		SetActive(false);
	}

}

void Sprite::Render() {

	LIGHT light;
	light.Enable = false;
	Renderer::SetLight(light);

	Renderer::SetWorldViewProjection2D();

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::GetDeviceContext()->Draw(4, 0);

}

void Sprite::SetTexture(ID3D11ShaderResourceView* value) {
	Texture = value;
}