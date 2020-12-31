/*
モデルクラス (Assimp)
*/

#pragma once

#include "Mesh.h"

class Asset;

class AssimpModel
{

private:

	// 名前
	std::string mName;
	// パス
	std::string mDirectory;
	// メッシュ
	std::vector<Mesh*> mMeshes;
	// テクスチャ (ロード)
	std::vector<Texture> mTexturesLoaded;
	// 法線テクスチャ (ロード)
	std::vector<Texture> mTexturesLoaded_Normal;
	// テクスチャ (選択)
	std::vector<Texture> mTexturesSelect;
	// アニメーション
	std::map < std::string, const aiScene*> mAnimation;
	// アニメーションチャンネル数
	std::vector<std::string> mAnimationChannel;

	// ロード処理
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMatrixerialTextures(aiMaterial* cmatrix, aiTextureType type, std::string typeName, const aiScene* scene);
	std::string DetermineTextureType(const aiScene* scene, aiMaterial* cmatrix);

	// ForDebug
	void DrawConfig();

	// 骨生成
	void CreateBone(aiNode* node, std::unordered_map <std::string, BONE> tBone);

	// Getter
	int GetTextureIndex(aiString* str);
	ID3D11ShaderResourceView* GetTextureFromModel(const aiScene* scene, int textureindex);

	const aiScene* mScene;

public:

	AssimpModel() = delete;
	AssimpModel(bool anicmatrixion) : Anicmatrixion(anicmatrixion) {};

	// リソース名前
	std::string mResourceName = "Model";

	// フラグ
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
	
	// 色設定
	void SetColorAll(D3DXCOLOR col);
	// テクスチャ (選択) 追加
	void PushTextureSelect(Asset* asset,int index);
};

