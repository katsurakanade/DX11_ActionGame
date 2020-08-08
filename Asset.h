#pragma 

#include "AssimpModel.h"
#include "model.h"

enum ASSIMP_MODEL_ENUM
{
	BALL,
	CUBE,
};

enum TEXTURE_ENUM {
	NUMBER,
	DIRT,
	METER,
	TOON,
	EXP,
	CAT,
};

class Asset
{

protected:

	static std::vector<AssimpModel*> AssimpModelList;
	static std::vector<ID3D11ShaderResourceView*> TextureList;

	// This Should Rewrite With Template
	static void AddAssimpModelToList(const char* value) {
		AssimpModel* md = new AssimpModel();
		md->Load(value);
		AssimpModelList.push_back(md);
	}

	static void AddTextureToList(const char* value) {
		ID3D11ShaderResourceView* tex;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		TextureList.push_back(tex);
	}


public:

	static void LoadSceneAsset();
	static void UnloadSceneAsset();
	
	static AssimpModel* GetAssimpModel(int index) { return AssimpModelList[index]; };
	static ID3D11ShaderResourceView* GetTexture(int index) { return TextureList[index]; };

	
	
};

