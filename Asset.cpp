#include "main.h"
#include "Renderer.h"
#include "Asset.h"

std::vector<AssimpModel*> Asset::mAssimpModelList;
std::vector<ID3D11ShaderResourceView*> Asset::mTextureList;

void Asset::LoadSceneAsset(){

	AddAssimpModelToList("asset\\model\\ball\\ball.obj");
	AddAssimpModelToList("asset\\model\\cube\\cube.obj");
	AddAssimpModelToList("asset\\model\\torus\\torus.obj");

	AddTextureToList("asset/texture/number.png");
	AddTextureToList("asset/texture/Dirt.jpg");
	AddTextureToList("asset/texture/meter.png");
	AddTextureToList("asset/texture/ToonMap.png");
	AddTextureToList("asset/texture/explosion2.png");
	AddTextureToList("asset/texture/cat.png");
	
}

void Asset::UnloadSceneAsset() {

	for (AssimpModel* md : mAssimpModelList) {
		md->Unload();
	}

	for (ID3D11ShaderResourceView* tex : mTextureList) {
		tex->Release();
	}

}