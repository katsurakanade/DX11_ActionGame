#include "main.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Scene.h"
#include "input.h"
#include "Shader.h"

void Sprite::Init() {

	Name = "Sprite";

	VERTEX_3D vertex[4];
	float col[4];

	Position = D3DXVECTOR3(0, 0, 0);

	vertex[0].Position = D3DXVECTOR3(Position.x, Position.y, 0.0f);
	vertex[1].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y, 0.0f);
	vertex[2].Position = D3DXVECTOR3(Position.x, Position.y + mSize.y, 0.0f);
	vertex[3].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y + mSize.y, 0.0f);

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

	col[0] = 1;
	col[1] = 1;
	col[2] = 1;
	col[3] = 1;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

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

	sd.pSysMem = col;

	Renderer::GetDevice()->CreateBuffer(&cbd, &sd, &mColorBuffer);

}

void Sprite::Uninit() {

	mVertexBuffer->Release();
	mColorBuffer->Release();
}

void Sprite::Update() {


	if (Input::GetKeyTrigger('B')) {
		SetActive(false);
	}

}

void Sprite::Render() {

	Renderer::SetWorldViewProjection2D();

	// アニメーション
	if (mAnimation) {

		D3DXVECTOR2 frame = MakeFrame();

		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(Position.x, Position.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(frame.x, frame.y);

		vertex[1].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(frame.x + (1.0f / mWidth), frame.y);

		vertex[2].Position = D3DXVECTOR3(Position.x, Position.y + mSize.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(frame.x, frame.y + (1.0f / mHeight));

		vertex[3].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y + mSize.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(frame.x + (1.0f / mWidth), frame.y + (1.0f / mHeight));

		Renderer::GetDeviceContext()->Unmap(mVertexBuffer, 0);
	}

	if (mFill) {
		SetPosition(D3DXVECTOR3(Position.x, Position.y,1));
	}

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &mColorBuffer);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture);
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Shader::Use(SHADER_TYPE_VSPS::Unlit);

	Renderer::GetDeviceContext()->Draw(4, 0);

}

void Sprite::SetTexture(ID3D11ShaderResourceView* value) {
	mTexture = value;
}

D3DXVECTOR2 Sprite::MakeFrame() {
	float x = mFramecount % mWidth * (1.0f / mWidth);
	float y = mFramecount / mHeight * (1.0f / mHeight);
	return D3DXVECTOR2(x, y);
}

void Sprite::SetPosition(D3DXVECTOR3 pos) {

	Position = pos;

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(Position.x, Position.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	vertex[1].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	vertex[2].Position = D3DXVECTOR3(Position.x, Position.y + mSize.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	vertex[3].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y + mSize.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	Renderer::GetDeviceContext()->Unmap(mVertexBuffer, 0);

}

void Sprite::SetColor(D3DXVECTOR4 col) {

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(mColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	float* colorbuf = (float*)msr.pData;

	colorbuf[0] = col.x;
	colorbuf[1] = col.y;
	colorbuf[2] = col.z;
	colorbuf[3] = col.w;

	Renderer::GetDeviceContext()->Unmap(mColorBuffer, 0);
}

void Sprite::SetSize(D3DXVECTOR3 value) {

	mSize = value;

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(Position.x, Position.y, 0.0f);
	vertex[1].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y, 0.0f);
	vertex[2].Position = D3DXVECTOR3(Position.x, Position.y + mSize.y, 0.0f);
	vertex[3].Position = D3DXVECTOR3(Position.x + mSize.x, Position.y + mSize.y, 0.0f);

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

	Renderer::GetDeviceContext()->Unmap(mVertexBuffer, 0);
}