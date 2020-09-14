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
	std::map < std::string, const aiScene*> mAnimation;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadcmatrixerialTextures(aiMaterial* cmatrix, aiTextureType type, std::string typeName, const aiScene* scene);
	std::string determineTextureType(const aiScene* scene, aiMaterial* cmatrix);

	void DrawConfig();

	void CreateBone(aiNode* node, std::unordered_map <std::string, BONE> tBone);

	int getTextureIndex(aiString* str);
	ID3D11ShaderResourceView* getTextureFromModel(const aiScene* scene, int textureindex);

	const aiScene* mScene;

public:

	AssimpModel() = delete;
	AssimpModel(bool anicmatrixion) : Anicmatrixion(anicmatrixion) {};

	bool DisplayConfig = false;
	bool DefaultTexture = true;
	bool Anicmatrixion = false;
	int SelectTextureIndex = 0;

	void Update(const char* animationname,int frame);
	void Draw(D3DXMATRIX root);
	void Load(std::string FileName);
	void LoadAnimation(std::string Filename, std::string name);
	void Unload();

	std::string GetDirectory() { return mDirectory; };
	std::vector<Mesh*> GetMeshes() { return mMeshes; };
	
	void SetColorAll(D3DXCOLOR col);

	void PushTextureSelect(Asset* asset,int index);
};

