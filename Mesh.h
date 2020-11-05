/*
���b�V���N���X
*/

#pragma once

// �e�N�X�`��
struct Texture {
	std::string type;
	std::string path;
	ID3D11ShaderResourceView* texture;
};

// �ό`
struct DEFORM_VERTEX {
	aiVector3D Position;
	aiVector3D Normal;
	int mBoneNum;
	std::string mBoneName[4];
	float mBoneWeight[4];
};

// ��
struct BONE {
	aiMatrix4x4 mMatrix;
	aiMatrix4x4 mAnimationMatrix;
	aiMatrix4x4 mOffsetMatirx;
};
// Compute Shader �p
struct COMPUTEMATRIX {
	aiMatrix4x4 cmatrix[4];
	float mBoneWeight[4];
};

class Mesh
{
private:

	bool SetupMesh();
	// Compute Shader �p
	void CreateComputeResource();
	void Process(VERTEX_3D* target,int index);
	void FillComputeMatrix();
	void FillVertex();

public:

	// �o�b�t�@
	ID3D11Buffer* VertexBuffer, * IndexBuffer, * ColorBuffer;

	ID3D11Buffer* mpBuf = nullptr;
	ID3D11Buffer* mpComputeBuf = nullptr;
	ID3D11Buffer* mpVerticesBuf = nullptr;
	ID3D11Buffer* resultbuffer = nullptr;
	// SRV
	ID3D11ShaderResourceView* mpBufSRV = nullptr;
	ID3D11ShaderResourceView* mpBoneBufSRV = nullptr;
	ID3D11ShaderResourceView* mpVerticesBufSRV = nullptr;
	// UAV
	ID3D11UnorderedAccessView* mpBufUAV = nullptr;

	// ���O
	std::string Name;
	// �e�N�X�`���p�X
	std::string TexturePass;
	// ���_
	std::vector <VERTEX_3D> Vertices;
	// �C���f�b�N�X
	std::vector <UINT> Indices;
	// �e�N�X�`��
	std::vector <Texture> Textures;
	// �e�N�X�`��
	std::vector <Texture> TexturesNormal;
	// �ό`���_
	std::vector <DEFORM_VERTEX> mDeformVertex;
	// Compute Shader �p
	std::vector <COMPUTEMATRIX> mComputeMatrix;
	// ��
	std::unordered_map <std::string, BONE> mBone;
	// �L��
	bool Enable;
	// �J���[
	float col[4] = { 1.0f,1.0f,1.0f,1.0f };
	// �}�e���A��
	MATERIAL Material;
	// �A�j���[�V��������
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
	// �A�j���[�V�����Ȃ�
	Mesh(std::string name, std::vector<VERTEX_3D> vertices, std::vector<UINT> indices, std::vector <Texture> textures, std::vector <Texture> texturesnormal, MATERIAL material) {

		this->Name = name;
		this->Vertices = vertices;
		this->Indices = indices;
		this->Textures = textures;
		this->Material = material;
		this->TexturesNormal = TexturesNormal;

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

