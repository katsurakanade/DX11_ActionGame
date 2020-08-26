#pragma once

struct Texture {
	std::string type;
	std::string path;
	ID3D11ShaderResourceView*  texture;
};

class Mesh{

private:

	ID3D11Buffer* VertexBuffer, * IndexBuffer , *ColorBuffer;

	bool SetupMesh()
	{

		HRESULT hr;

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_DYNAMIC;
		vbd.ByteWidth = UINT(sizeof(VERTEX_3D) * Vertices.size());
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &Vertices[0];

		hr = Renderer::GetDevice()->CreateBuffer(&vbd, &initData, &VertexBuffer);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_DYNAMIC;
		ibd.ByteWidth = sizeof(UINT) * UINT(Indices.size());
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ibd.MiscFlags = 0;

		initData.pSysMem = &Indices[0];

		hr = Renderer::GetDevice()->CreateBuffer(&ibd, &initData, &IndexBuffer);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC cbd;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.ByteWidth = sizeof(col);
		cbd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;

		initData.pSysMem = &col[0];

		hr = Renderer::GetDevice()->CreateBuffer(&cbd, &initData, &ColorBuffer);
		if (FAILED(hr))
			return false;

		return true;
	}
	
public:

	std::string Name;
	std::string TexturePass;
	std::vector <VERTEX_3D> Vertices;
	std::vector <UINT> Indices;
	std::vector <Texture> Textures;

	bool Enable;

	float col[4] = {1.0f,1.0f,1.0f,1.0f};

	MATERIAL Material;

	Mesh(std::string name,std::vector<VERTEX_3D> vertices, std::vector<UINT> indices, std::vector <Texture> textures, MATERIAL material) {

		this->Name = name;
		this->Vertices = vertices;
		this->Indices = indices;
		this->Textures = textures;
		this->Material = material;
		
		this->Enable = true;

		this->SetupMesh();
		
		D3DXQuaternionIdentity(&Quaternion);
	};

	D3DXQUATERNION Quaternion;

	D3DXVECTOR3 Position = D3DXVECTOR3(0.0, 0.0, 0.0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0.0, 0.0, 0.0);
	D3DXVECTOR3 Scale = D3DXVECTOR3(1.0, 1.0, 1.0);

	void Draw() {

		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(ColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		float *col = (float*)msr.pData;
		col[0] = this->col[0];
		col[1] = this->col[1];
		col[2] = this->col[2];
		col[3] = this->col[3];
		Renderer::GetDeviceContext()->Unmap(ColorBuffer, 0);

		Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &ColorBuffer);

		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
		Renderer::GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		if (!Renderer::mLineMode) {
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		else {
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		}

		Renderer::SetMaterial(Material);

		Renderer::GetDeviceContext()->DrawIndexed((UINT)Indices.size(), 0, 0);
	};

	void Close() {
		VertexBuffer->Release();
		IndexBuffer->Release();
	}

};

class AssimpModel
{

private:

	std::string Name;

	D3DXVECTOR2 ConfigPos;

	std::string Directory;
	std::vector<Mesh> Meshes;
	std::vector<Texture> textures_loaded;
	std::vector<Texture> textures_select;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
	std::string determineTextureType(const aiScene* scene, aiMaterial* mat);

	void DrawConfig();

	int getTextureIndex(aiString* str);
	ID3D11ShaderResourceView* getTextureFromModel(const aiScene* scene, int textureindex);

public:

	bool DisplayConfig = false;
	bool DefaultTexture = true;
	int SelectTextureIndex = 0;
	void SetConfingPos(D3DXVECTOR2 pos) { ConfigPos = pos; };

	void Draw(D3DXMATRIX root);
	void Load(std::string FileName);
	void Unload();

	void MeshRotate(int index, float val) { Meshes[index].Rotation.x += val; };

	std::string GetDirectory() { return Directory; };
	std::vector<Mesh> GetMeshes() { return Meshes; };
	
	void SetColorAll(D3DXCOLOR col) {
		for (int i = 0; i < Meshes.size();i++) {
			Meshes[i].col[0] = col.r;
			Meshes[i].col[1] = col.g;
			Meshes[i].col[2] = col.b;
			Meshes[i].col[3] = col.a;
		}
	};

	void PushTextureSelect(int index);
};

