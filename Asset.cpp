#include "main.h"
#include "Renderer.h"
#include "Asset.h"

std::vector<AssimpModel*> Asset::mAssimpModelList;
std::vector<ID3D11ShaderResourceView*> Asset::mTextureList;

void Asset::LoadSceneAsset(){

	AddAssimpModelToList("asset\\model\\ball\\ball.obj");
	AddAssimpModelToList("asset\\model\\cube\\cube.obj");
	AddAssimpModelToList("asset\\model\\torus\\torus.obj");
	AddAssimpModelToList("asset\\model\\arrow\\arrow.obj");
	AddAssimpModelToList("asset\\model\\enemy\\enemy.obj");

	AddTextureToList("asset/texture/number.png");
	AddTextureToList("asset/texture/Dirt.jpg");
	AddTextureToList("asset/texture/meter.png");
	AddTextureToList("asset/texture/ToonMap.png");
	AddTextureToList("asset/texture/explosion2.png");
	AddTextureToList("asset/texture/Wizard.png");
	AddTextureToList("asset/texture/Samurai.png");
	AddTextureToList("asset/texture/Warrior.png");
	AddTextureToList("asset/texture/Elf.png");
	AddTextureToList("asset/texture/bar_empty.png");
	AddTextureToList("asset/texture/bar_fill.png");
	AddTextureToList("asset/texture/Clear.png");

	mAssimpModelList[ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect(TEXTURE_ENUM::SAMURAI);
	mAssimpModelList[ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect(TEXTURE_ENUM::WIZARD);
	mAssimpModelList[ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect(TEXTURE_ENUM::WARRIOR);
	mAssimpModelList[ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect(TEXTURE_ENUM::ELF);
}

void Asset::UnloadSceneAsset() {

	for (AssimpModel* md : mAssimpModelList) {
		md->Unload();
	}

	for (ID3D11ShaderResourceView* tex : mTextureList) {
		tex->Release();
	}

}