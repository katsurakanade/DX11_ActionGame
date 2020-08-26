#pragma 

#include "AssimpModel.h"

enum class ASSIMP_MODEL_ENUM
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
	EXP,
	WIZARD,
	SAMURAI,
	WARRIOR,
	ELF,
	BAR_EMPTY,
	BAR_FILL,
	CLEAR,
	LOGO,
	WHITE
};

class Asset
{

protected:

	static std::vector<AssimpModel*> mAssimpModelList;
	static std::vector<ID3D11ShaderResourceView*> mTextureList;

	static void AddAssimpModelToList(const char* value) {

		AssimpModel* md = new AssimpModel();
		md->Load(value);
		mAssimpModelList.emplace_back(md);
	}

	static void AddTextureToList(const char* value) {
		ID3D11ShaderResourceView* tex;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		mTextureList.emplace_back(tex);
	}

public:

	static void LoadSceneAsset();
	static void UnloadSceneAsset();
	
	static AssimpModel* GetAssimpModel(ASSIMP_MODEL_ENUM index) { return mAssimpModelList[(int)index]; };
	static ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };

};

