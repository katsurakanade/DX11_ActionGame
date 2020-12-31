/*
���f���N���X (Assimp)
*/

#pragma once

#include "Mesh.h"

class Asset;

class AssimpModel
{

private:

	// ���O
	std::string mName;
	// �p�X
	std::string mDirectory;
	// ���b�V��
	std::vector<Mesh*> mMeshes;
	// �e�N�X�`�� (���[�h)
	std::vector<Texture> mTexturesLoaded;
	// �@���e�N�X�`�� (���[�h)
	std::vector<Texture> mTexturesLoaded_Normal;
	// �e�N�X�`�� (�I��)
	std::vector<Texture> mTexturesSelect;
	// �A�j���[�V����
	std::map < std::string, const aiScene*> mAnimation;
	// �A�j���[�V�����`�����l����
	std::vector<std::string> mAnimationChannel;

	// ���[�h����
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMatrixerialTextures(aiMaterial* cmatrix, aiTextureType type, std::string typeName, const aiScene* scene);
	std::string DetermineTextureType(const aiScene* scene, aiMaterial* cmatrix);

	// ForDebug
	void DrawConfig();

	// ������
	void CreateBone(aiNode* node, std::unordered_map <std::string, BONE> tBone);

	// Getter
	int GetTextureIndex(aiString* str);
	ID3D11ShaderResourceView* GetTextureFromModel(const aiScene* scene, int textureindex);

	const aiScene* mScene;

public:

	AssimpModel() = delete;
	AssimpModel(bool anicmatrixion) : Anicmatrixion(anicmatrixion) {};

	// ���\�[�X���O
	std::string mResourceName = "Model";

	// �t���O
	bool DisplayConfig = false;
	bool DefaultTexture = true;
	bool Anicmatrixion = false;
	int SelectTextureIndex = 0;

	void Update(const char* animationname,int frame);
	void Update(const char* animationname, const char* animationname2, float BlendRate, int frame);
	void Draw(D3DXMATRIX root);
	bool Load(std::string FileName);
	bool LoadAnimation(std::string Filename, std::string name);
	void Unload();

	// Getter
	std::string GetDirectory() { return mDirectory; };
	std::vector<Mesh*> GetMeshes() { return mMeshes; };
	
	// �F�ݒ�
	void SetColorAll(D3DXCOLOR col);
	// �e�N�X�`�� (�I��) �ǉ�
	void PushTextureSelect(Asset* asset,int index);
};

