#include "main.h"
#include "renderer.h"
#include "MeshField.h"
#include "Application.h"
#include "Shader.h"
#include "FileManger.h"
#include "ModelManager.h"
#include "Grass.h"
#include "Props.h"
#include <random>

float MeshField::HeightMap[FIELD_X][FIELD_X];

void MeshField::Init() {

	// マップ上のオブジェクトロード
	FileManager::ReadResource("asset\\json_scene_object\\grass.json");
	FileManager::ReadResource("asset\\json_scene_object\\props.json");
	// マップロード（画像）
	FileManager::ReadImageMap("asset/texture/map2.bmp",MeshField::HeightMap);

	Name = "MeshField";

	// 頂点
	for (int x = 0; x <= FIELD_X - 1; x++) {
		for (int z = 0; z <= FIELD_X - 1; z++) {
			float y = HeightMap[x][z];
			mVertex[x][z].Position = D3DXVECTOR3((x - 10) * 10.0f, y, (z - 10) * -10.0f);
			mVertex[x][z].Normal = D3DXVECTOR3(0, 1, 0);
			mVertex[x][z].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
			mVertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
		}
	}

	// 法線
	for (int x = 1; x <= FIELD_X - 2; x++) {
		for (int z = 1; z <= FIELD_X - 2; z++) {
			D3DXVECTOR3 vx, vz, vn;
			vx = mVertex[x + 1][z].Position - mVertex[x - 1][z].Position;
			vz = mVertex[x][z - 1].Position - mVertex[x][z + 1].Position;
			D3DXVec3Cross(&vn, &vz, &vx);
			D3DXVec3Normalize(&vn, &vn);
			mVertex[x][z].Normal = vn;
		}
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * FIELD_X * FIELD_X;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	// Index Buffer
	{
		unsigned int index[((FIELD_X+1) * 2) * (FIELD_X-1) - 2];
		int i = 0;
		for (int x = 0; x < FIELD_X - 1; x++) {
			for (int z = 0; z < FIELD_X; z++) {
				index[i] = x * FIELD_X + z;
				i++;
				index[i] = (x + 1) * FIELD_X + z;
				i++;
			}
			if (x == FIELD_X-2) {
				break;
			}

			index[i] = (x + 1) * FIELD_X + (FIELD_X - 1);
			i++;
			index[i] = (x + 1) * FIELD_X;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (((FIELD_X + 1)*2) * (FIELD_X - 1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mIndexBuffer);
	}

	// 画像
	mTexture.push_back(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::DIRT));
	mTextureNormal.push_back(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::DIRT_NORMAL));
	mTextureHeight.push_back(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::DIRT_HEIGHT));

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	D3DXMATRIX world = MakeWorldMatrix();
	Renderer::SetWorldMatrix(&world);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer,DXGI_FORMAT_R32_UINT,0);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Shininess = 225;
	Renderer::SetMaterial(material);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture[0]);
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &mTextureNormal[0]);
	Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &mTextureHeight[0]);

	if (!Renderer::mLineMode) {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	else {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}

	Shader::Use(SHADER_TYPE_VSPS::WithHeight);

	Renderer::GetDeviceContext()->DrawIndexed(((FIELD_X + 1)*2) * (FIELD_X - 1) -2,0, 0);
	
}

float MeshField::GetHeight(D3DXVECTOR3 pos) {

	int x, z;
	x = pos.x / 10 + 10;
	z = pos.z / -10 + 10;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = mVertex[x][z].Position;
	pos1 = mVertex[x + 1][z].Position;
	pos2 = mVertex[x][z+1].Position;
	pos3 = mVertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;
	v1p = pos - pos1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y > 0.0f) {
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else {
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	py = -((pos.x - pos1.x) * n.x + (pos.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}