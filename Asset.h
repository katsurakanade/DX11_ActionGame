#pragma 

#include "AssimpModel.h"

enum ASSIMP_MODEL_ENUM
{
	BALL,
	CUBE,
	TORUS,
	ARROW,
	ENEMY,
};

enum TEXTURE_ENUM {
	NUMBER,
	DIRT,
	METER,
	TOON,
	EXP,
	WIZARD,
	SAMURAI,
};

class Asset
{

protected:

	static std::vector<AssimpModel*> mAssimpModelList;
	static std::vector<ID3D11ShaderResourceView*> mTextureList;

	static void AddAssimpModelToList(const char* value) {
		AssimpModel* md = new AssimpModel();
		md->Load(value);
		mAssimpModelList.push_back(md);
	}

	static void AddTextureToList(const char* value) {
		ID3D11ShaderResourceView* tex;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		mTextureList.push_back(tex);
	}


public:

	static void LoadSceneAsset();
	static void UnloadSceneAsset();
	
	static AssimpModel* GetAssimpModel(int index) { return mAssimpModelList[index]; };
	static ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };

};

