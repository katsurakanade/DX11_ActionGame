#include "main.h"
#include "renderer.h"
#include "MeshField.h"
#include "Application.h"
#include "Shader.h"
#include <random>

void MeshField::Init() {

	Name = "MeshField";

	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_real_distribution<float> dis(0.1f, 0.5f);

	for (int x = 0; x <= 20; x++) {
		for (int z = 0; z <= 20; z++) {
			mVertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, dis(gen), (z - 10) * -5.0f);
			mVertex[x][z].Normal = D3DXVECTOR3(0, 1, 0);
			mVertex[x][z].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
			mVertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
		}
	}

	for (int x = 1; x <= 19; x++) {

	}


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	// Index Buffer
	{
		unsigned int index[(22 * 2) * 20 - 2];
		int i = 0;
		for (int x = 0; x < 20; x++) {
			for (int z = 0; z < 21; z++) {
				index[i] = x * 21 + z;
				i++;
				index[i] = (x + 1) * 21 + z;
				i++;
			}
			if (x == 19) {
				break;
			}

			index[i] = (x + 1) * 21 + 20;
			i++;
			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22*2) * 20 - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mIndexBuffer);
	}

	mTexture = Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::WOOD);

	Position = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&Quaternion);
}

void MeshField::Unint() {
	mVertexBuffer->Release();
	mIndexBuffer->Release();
}

void MeshField::Update() {

}

void MeshField::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer,DXGI_FORMAT_R32_UINT,0);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture);

	if (!Renderer::mLineMode) {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	else {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}

	Shader::Use(SHADER_TYPE_VSPS::Default);

	Renderer::GetDeviceContext()->DrawIndexed((22*2) * 20 - 2,0, 0);
}