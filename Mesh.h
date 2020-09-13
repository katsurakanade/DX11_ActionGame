#pragma once

struct Texture {
	std::string type;
	std::string path;
	ID3D11ShaderResourceView* texture;
};

struct DEFORM_VERTEX {
	aiVector3D Position;
	aiVector3D Normal;
	int mBoneNum;
	std::string mBoneName[4];
	float mBoneWeight[4];
};

struct BONE {
	aiMatrix4x4 mMatrix;
	aiMatrix4x4 mAnimationMatrix;
	aiMatrix4x4 mOffsetMatirx;
};

struct COMPUTEMATRIX {
	aiMatrix4x4 outMatrix;
};

class Mesh
{
private:

	bool SetupMesh();
	void CreateComputeResource();

public:
	ID3D11Buffer* VertexBuffer, * IndexBuffer, * ColorBuffer;

	ID3D11Buffer* mpBuf = nullptr;
	ID3D11Buffer* mpBoneBuf = nullptr;
	ID3D11Buffer* mpVerticesBuf = nullptr;
	ID3D11ShaderResourceView* mpBufSRV = nullptr;
	ID3D11ShaderResourceView* mpBoneBufSRV = nullptr;
	ID3D11ShaderResourceView* mpVerticesBufSRV = nullptr;
	ID3D11Buffer* resultbuffer = nullptr;;
	ID3D11UnorderedAccessView* mpBufUAV = nullptr;

	std::string Name;
	std::string TexturePass;
	std::vector <VERTEX_3D> Vertices;
	std::vector <UINT> Indices;
	std::vector <Texture> Textures;
	std::vector <DEFORM_VERTEX> mDeformVertex;
	std::vector <COMPUTEMATRIX> mComputeMatrix;
	std::unordered_map <std::string, BONE> mBone;

	bool Enable;

	float col[4] = { 1.0f,1.0f,1.0f,1.0f };

	MATERIAL Material;

	Mesh(std::string name, std::vector<VERTEX_3D> vertices, std::vector<UINT> indices, std::vector <Texture> textures, MATERIAL material, std::vector <DEFORM_VERTEX> deform, std::unordered_map  <std::string, BONE> bone) {

		this->Name = name;
		this->Vertices = vertices;
		this->Indices = indices;
		this->Textures = textures;
		this->Material = material;
		this->mDeformVertex = deform;
		this->mBone = bone;

		this->Enable = true;
		this->SetupMesh();
		this->CreateComputeResource();

		D3DXQuaternionIdentity(&Quaternion);

	};

	Mesh(std::string name, std::vector<VERTEX_3D> vertices, std::vector<UINT> indices, std::vector <Texture> textures, MATERIAL material) {

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

	void Update();

	void Draw();

	void Close();

	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);
};

