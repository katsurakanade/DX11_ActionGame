#pragma once

#include "Mesh.h"

class Asset;

class AssimpModel
{

private:

	std::string mName;

	std::string mDirectory;
	std::vector<Mesh*> mMeshes;
	std::vector<Texture> mTexturesLoaded;
	std::vector<Texture> mTexturesSelect;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
	std::string determineTextureType(const aiScene* scene, aiMaterial* mat);

	void DrawConfig();

	void CreateBone(aiNode* node, std::map <const std::string, BONE> tBone);

	int getTextureIndex(aiString* str);
	ID3D11ShaderResourceView* getTextureFromModel(const aiScene* scene, int textureindex);

	const aiScene* mScene;

public:

	AssimpModel() = delete;
	AssimpModel(bool animation) : Animation(animation) {};

	bool DisplayConfig = false;
	bool DefaultTexture = true;
	bool Animation = false;
	int SelectTextureIndex = 0;

	void Update(int frame);
	void Draw(D3DXMATRIX root);
	void Load(std::string FileName);
	void Unload();

	std::string GetDirectory() { return mDirectory; };
	std::vector<Mesh*> GetMeshes() { return mMeshes; };
	
	void SetColorAll(D3DXCOLOR col);

	void PushTextureSelect(Asset* asset,int index);
};

